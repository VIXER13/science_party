#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace conference {

enum class scientific_interest : uint8_t {
    Begin,
    Epidemiology = Begin,
    Statistics,
    Clinical_Investigations,
    Healt_Policy,
    End
};

std::ostream& operator<<(std::ostream& os, scientific_interest interest);

struct person final {
    std::string name;
    uint64_t id;
    scientific_interest interest;

    friend std::ostream& operator<<(std::ostream& os, const person& p);
};

std::vector<person> invite_guests(size_t number);

}