#include "finder.hpp"
#include <iostream>


int main() {

    path result;
    try {
        result = font_finder::find_font("asdklfasdf");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Result: " << std::endl;
    std::cout << result << std::endl;

    return EXIT_SUCCESS;
}
