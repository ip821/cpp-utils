#pragma once

#include <fmt/format.h>
#include <wx/string.h>

template<>
struct fmt::formatter<wxString> : fmt::formatter<std::string_view>
{
    auto format(const wxString& value, fmt::format_context& ctx) const
    {
        const std::string utf8 = value.utf8_string();
        return fmt::formatter<std::string_view>::format(utf8, ctx);
    }
};
