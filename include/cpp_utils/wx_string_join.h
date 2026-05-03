#pragma once

#include  <wx/string.h>

namespace ip
{
    template<std::ranges::input_range Range>
    wxString wxJoin(const Range& strings, const wxString& separator)
    {
        wxString result;

        const auto lastElementIndex = strings.size() - 1;
        for (size_t index = 0; const auto& str: strings)
        {
            result += str;

            if (index != lastElementIndex)
                result += separator;

            index++;
        }
        return result;
    }
}
