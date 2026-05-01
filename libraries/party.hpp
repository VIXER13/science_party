#pragma once

#include "guests.hpp"

namespace conference {

using guests_in_room_a = std::vector<person>;
using guests_in_room_b = std::vector<std::pair<person, person>>;

std::pair<guests_in_room_a, guests_in_room_b> simulate_party(size_t guests_number, size_t time_limit);

}