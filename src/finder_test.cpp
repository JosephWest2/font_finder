#include "finder.hpp"
#include <filesystem>
#include <iostream>

using std::filesystem::path;

int main() {

    path result;
    try {
        result = font_finder::find_font("HackNerdFont");
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        result = font_finder::find_font("HackNerdFont", "Bold", {"/home/josephwest/.local/share/fonts", "/usr/share/fonts"});
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Result: " << result << std::endl;

    return EXIT_SUCCESS;
}
