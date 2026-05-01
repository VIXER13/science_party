#include <party.hpp>
#include <utils.hpp>

#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Input format: [program name] guests_number party_duration" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        const auto [room_a, room_b] = conference::simulate_party(utils::get_number(argv[1]), utils::get_number(argv[2]));
        std::cout << std::endl;
        conference::show_guests_info(room_a);
        std::cout << std::endl;
        conference::show_guests_info(room_b);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Something went wrong..." << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}