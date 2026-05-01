#include <party.hpp>

#include <iostream>

int main(int argc, char** argv) {
    int result = EXIT_SUCCESS;
    try {
        conference::simulate_party(50, 25);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        result = EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Something went wrong..." << std::endl;
        result = EXIT_FAILURE;
    }
    return result;
}