#pragma once

#include <concepts>
#include <filesystem>
#include <initializer_list>
#include <ranges>
#include <string>

using std::convertible_to;
using std::string;
using std::string_view;
using std::filesystem::path;
using std::ranges::input_range;
using std::ranges::range_reference_t;

namespace font_finder {
// Searches common os directories for a font,
// optionally takes in additional directories to check, and a font style (ie Regular, Bold, Italic)
// throws an error if no font is found
template <typename R>
    requires input_range<R> && convertible_to<range_reference_t<R>, string_view>
path find_font(string name, string style = "Regular", R&& search_directories = {});

// Searches common os directories for a font,
// optionally takes in additional directories to check, and a font style (ie Regular, Bold, Italic)
// throws an error if no font is found
path find_font(string name, string style = "Regular");

// Searches common os directories for a font,
// optionally takes in additional directories to check, and a font style (ie Regular, Bold, Italic)
// throws an error if no font is found
path find_font(string name, string style, std::initializer_list<string_view> search_directories);
}  // namespace font_finder
