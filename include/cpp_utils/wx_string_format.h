#pragma once

template<>
struct std::formatter<wxString, char> : std::formatter<std::string, char>
{
    auto format(const wxString& value, std::format_context& ctx) const
    {
        auto utf8 = value.ToUTF8();

        std::string s = utf8.data()
            ? std::string(utf8.data())
            : std::string{};

        return std::formatter<std::string, char>::format(s, ctx);
    }
};

template<>
struct std::formatter<wxString, wchar_t> : std::formatter<std::wstring, wchar_t>
{
    auto format(const wxString& value, std::wformat_context& ctx) const
    {
        return std::formatter<std::wstring, wchar_t>::format(
            value.ToStdWstring(),
            ctx
        );
    }
};
