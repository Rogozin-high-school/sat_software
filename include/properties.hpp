#pragma once

#include <string>
#include <optional>

using optional_string = const std::optional<const std::string_view>;
using optional_int = const std::optional<int>;

struct Properties
{
    static bool load() noexcept;
    static optional_string get_string(std::string&& property) noexcept; 
    static optional_int get_int(std::string&& property) noexcept; 
};