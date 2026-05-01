#pragma once

#include "guests.hpp"

#include <optional>

namespace conference {

enum class Room : bool { A, B };

using guests_in_room_a = std::vector<person>;
using guests_in_room_b = std::vector<std::pair<person, person>>;

std::pair<guests_in_room_a, guests_in_room_b> simulate_party(size_t guests_number, size_t time_limit);

bool in_room(const guests_in_room_a& guests, size_t id);
bool in_room(const guests_in_room_b& guests, size_t id);
std::optional<Room> in_room(const guests_in_room_a& alone_guests, const guests_in_room_b& coupled_guests, size_t id);

void show_guests_info(const guests_in_room_a& guests);
void show_guests_info(const guests_in_room_b& guests);

}

namespace conference::details {

using common_interests = std::array<size_t, size_t(scientific_interest::End)>;

common_interests get_common_interests(const std::vector<person>& guests);
bool have_common_interests(const common_interests& interests);
void leave_room(std::vector<person>& guests_in_room, size_t first, size_t second);

}