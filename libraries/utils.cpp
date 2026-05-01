#include "utils.hpp"

#include <stdexcept>

namespace utils {

size_t get_number(const std::string& number) {
    if (number[0] == '-')
        throw std::domain_error{"The number cannot be negative"};
    return std::stoull(number);
}

}