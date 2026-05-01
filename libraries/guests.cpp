#include "guests.hpp"

#include <algorithm>
#include <array>
#include <ostream>
#include <random>
#include <ranges>

namespace {

using namespace conference;

constexpr auto Name_Pool = std::array{
    "James", "Emma", "Liam", "Sophia", "Noah", "Olivia", "Ethan", "Ava", 
    "Mason", "Isabella", "Lucas", "Mia", "Logan", "Amelia", "Elijah", 
    "Charlotte", "Oliver", "Evelyn", "Benjamin", "Abigail", "Alexander", 
    "Emily", "Michael", "Harper", "Daniel", "Elizabeth", "William", 
    "Sofia", "Matthew", "Avery", "Joseph", "Ella", "Jackson", "Madison", 
    "Samuel", "Scarlett", "David", "Victoria", "John", "Aria", "Owen", 
    "Grace", "Wyatt", "Chloe", "Julian", "Camila", "Levi", "Penelope", 
    "Isaac", "Riley"
};

std::string_view to_string_view(scientific_interest interest) {
    switch (interest) {
        case scientific_interest::Epidemiology:
            return "Epidemiology";
        case scientific_interest::Statistics:
            return "Statistics";
        case scientific_interest::Clinical_Investigations:
            return "Clinical_Investigations";
        case scientific_interest::Healt_Policy:
            return "Healt_Policy";
        default:
            return "Other";
    }
}

}

namespace conference {

std::ostream& operator<<(std::ostream& os, scientific_interest interest) {
    os << to_string_view(interest);
    return os;
}

std::ostream& operator<<(std::ostream& os, const person& p) {
    os << p.name << '(' << p.id << ')';
    return os;
}

std::vector<person> invite_guests(size_t number) {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<size_t> name_distribution{0zu, Name_Pool.size() - 1zu};
    std::uniform_int_distribution<> interests_distribution{int(scientific_interest::Begin), int(scientific_interest::End) - 1};
    std::vector<person> guests;
    guests.reserve(number);
    for(const size_t i : std::ranges::iota_view{0zu, number})
        guests.push_back(person{
            .name = Name_Pool[name_distribution(gen)],
            .id = i,
            .interest = scientific_interest(interests_distribution(gen))
        });
    return guests;
}

}