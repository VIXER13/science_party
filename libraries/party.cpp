#include "party.hpp"

#include <exception>
#include <iostream>
#include <random>
#include <ranges>

namespace {

using namespace conference;

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
    guests_in_room_a guests = invite_guests(guests_number);
    guests_in_room_b couples;
    for (const size_t t : std::ranges::iota_view{0zu, time_limit}) {
        if (const auto [first, second] = get_random_pair(guests);
            guests[first].interest == guests[second].interest) {
            std::cout << guests[first] << " meet " << guests[second]
                      << " and they found an interest in " << guests[first].interest << std::endl;
            couples.emplace_back(std::move(guests[first]), std::move(guests[second]));
            leave_room(guests, first, second);
        } else {
            std::cout << guests[first] << " meet " << guests[second]
                      << " but their interests did not match." << std::endl;
        }
    }
    return {std::move(guests), std::move(couples)};
}

}