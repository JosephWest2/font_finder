#include "finder.hpp"
#include <cctype>
#include <filesystem>
#include <iostream>
#include <unordered_set>
#include <vector>

using std::vector;
using std::cerr;
using std::endl;
using std::filesystem::is_directory;
using std::filesystem::is_regular_file;
using std::filesystem::directory_iterator;
using std::unordered_set;
using std::string;
using std::transform;
using std::filesystem::path;

namespace font_finder {

std::filesystem::path find_font(std::string name, std::string style, const std::vector<std::filesystem::path>& search_directories) {

    vector<path> directories{};
    for (auto& directory : search_directories) {
        directories.push_back(path(directory));
    }

#ifdef __linux__

    char* home = getenv("HOME");
    if (home == nullptr) {
        cerr << "HOME environment variable not set, not searching home directory" << endl;
    } else {
        directories.push_back(path(home) / ".local/share/fonts");
    }
    directories.push_back("/usr/share/fonts");

#elif __APPLE__

    char* home = getenv("HOME");
    if (home == nullptr) {
        cerr << "HOME environment variable not set, not searching home directory" << endl;
    } else {
        directories.push_back(path(home) / "Library/Fonts");
    }
    directories.push_back("/Library/Fonts");

#elif _WIN32

    char* user_profile = getenv("USERPROFILE");
    if (user_profile == nullptr) {
        cerr << "USERPROFILE environment variable not set, not searching appdata directory" << endl;
    } else {
        directories.push_back(path(user_profile) / "AppData/Local/Microsoft/Windows/Fonts");
    }
    directories.push_back(path("C:\\Windows\\Fonts"));

#else 
#error "Unsupported OS"
#endif

    transform(name.begin(), name.end(), name.begin(), ::tolower);
    transform(style.begin(), style.end(), style.begin(), ::tolower);
    unordered_set<string> matches{
        name + ".ttf",
        name + "-" + style + ".ttf"
    };

    unordered_set<path> visited{};

    while (!directories.empty()) {
        const auto directory = directories.back();
        directories.pop_back();
        try {
            for (const auto& entry : directory_iterator(directory)) {
                visited.insert(directory);
                if (is_directory(entry)) {
                    if (visited.contains(entry.path())) {
                        continue;
                    }
                    directories.push_back(entry.path());
                } else if (is_regular_file(entry)) {
                    string entry_name = entry.path().filename().string();
                    transform(entry_name.begin(), entry_name.end(), entry_name.begin(), ::tolower);
                    if (matches.contains(entry_name)) {
                        return entry.path();
                    }
                }
            }

        } catch (std::filesystem::filesystem_error& e) {
            cerr << e.what() << endl;
        }
    }
    string error_message = "Font not found, searched directories:\n";
    for (const auto& directory : visited) {
        error_message += directory.string() + "\n";
    }
    throw std::runtime_error(error_message);
}

}  // namespace font_finder
