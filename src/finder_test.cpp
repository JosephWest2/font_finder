#include "finder.hpp"
#include <iostream>


int main() {

    path result;
    try {
        result = font_finder::find_font("asdklfasdf", "bold");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        result = font_finder::find_font("HackNerdFont", "Bold");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Result: " << result << std::endl;

    return EXIT_SUCCESS;
}
