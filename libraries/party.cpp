#include "party.hpp"

#include <algorithm>
#include <exception>
#include <iostream>
#include <random>
#include <ranges>

namespace {

using namespace conference;
using common_interests = std::array<size_t, size_t(scientific_interest::End)>;

common_interests get_common_interests(const std::vector<person>& guests) {
    common_interests result = {};
    for(const auto& guest : guests)
        ++result[size_t(guest.interest)];
    return result;
}

bool have_common_interests(const common_interests& interests) {
    return std::any_of(interests.begin(), interests.end(), [](size_t number) { return number > 1zu; });
}

std::pair<size_t, size_t> get_random_pair(const std::vector<person>& guests) {
    if (guests.size() < 2)
        throw std::domain_error{"To get a pair, the number of guests shall be more than 1."};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<size_t> guests_distribution{0zu, guests.size() - 1zu};
    const size_t first = guests_distribution(gen);
    size_t second = first;
    while (second == first)
        second = guests_distribution(gen);
    return {first, second};
}

void leave_room(std::vector<person>& guests_in_room, size_t first, size_t second) {
    if (first >= guests_in_room.size() || second >= guests_in_room.size())
        throw std::out_of_range{"Invalid guest id."};

    const auto pop_guest = [&guests_in_room](size_t id) {
        std::swap(guests_in_room[id], guests_in_room.back());
        guests_in_room.pop_back();
    };

    if (first == second) {
        pop_guest(first);
        return;
    }

    if (first < second)
        std::swap(first, second);
    pop_guest(first);
    pop_guest(second);
}

}

namespace conference {

std::pair<guests_in_room_a, guests_in_room_b> simulate_party(size_t guests_number, size_t time_limit) {
    if (guests_number == 0)
        throw std::domain_error{"It seems like no one came to the party..."};
    if (guests_number == 1)
        throw std::domain_error{"It seems the organizer forgot to invite guests to the party and showed up alone."};
    if (time_limit == 0)
        throw std::domain_error{"You have set too little time for this event.."};

    guests_in_room_a guests = invite_guests(guests_number);
    guests_in_room_b couples;
    auto interests = get_common_interests(guests);
    for (const size_t t : std::ranges::iota_view{0zu, time_limit}) {
        if (!have_common_interests(interests)) {
            std::cout << "The party ended early because the guests had no common interests." << std::endl;
            break;
        }

        if (const auto [first, second] = get_random_pair(guests);
            guests[first].interest == guests[second].interest) {
            std::cout << guests[first] << " meet " << guests[second]
                      << " and they found an interest in " << guests[first].interest << std::endl;
            interests[size_t(guests[first].interest)] -= 2;
            couples.emplace_back(std::move(guests[first]), std::move(guests[second]));
            leave_room(guests, first, second);
        } else {
            std::cout << guests[first] << " meet " << guests[second]
                      << " but their interests did not match." << std::endl;
        }
    }
    if (have_common_interests(interests))
        std::cout << "The guests didn't have enough time to get to know everyone." << std::endl;
    return {std::move(guests), std::move(couples)};
}

bool in_room(const guests_in_room_a& guests, size_t id) {
    return std::any_of(guests.begin(), guests.end(), [id](const person& guest) {
        return guest.id == id;
    });
}

bool in_room(const guests_in_room_b& guests, size_t id) {
    return std::any_of(guests.begin(), guests.end(), [id](const auto& couple) {
        const auto& [first, second] = couple;
        return first.id == id || second.id == id;
    });
}

void show_guests_info(const guests_in_room_a& guests) {
    std::cout << (guests.empty() ? "No one in the room A."
                                 : "There are guests in the room A:") << std::endl;
    for(const auto& guest : guests)
        std::cout << guest << " with interest " << guest.interest << std::endl;
}

void show_guests_info(const guests_in_room_b& guests) {
    std::cout << (guests.empty() ? "No one in the room B."
                                 : "There are couple of guests in the room B:") << std::endl;
    for(const auto& [first, second] : guests)
        std::cout << first << " and " << second << " have common interest in " << first.interest << std::endl;
}

}