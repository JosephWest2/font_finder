#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace font_finder {
// Searches common os directories for a font,
// optionally takes in additional directories to check, and a font style (ie Regular, Bold, Italic)
// throws an error if no font is found
std::filesystem::path find_font(std::string name, std::string style = "Regular", const std::vector<std::filesystem::path>& search_directories = {});

}  // namespace font_finder
