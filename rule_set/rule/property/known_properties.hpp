#pragma once

#include "valueifier.hpp"

#include "value.hpp"

#include "mplex/fundamental/null_type.hpp"
#include "mplex/string/string.hpp"
#include "mplex/string/inline_string.hpp"

#include <tuple>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace WretchedCss
{
    using namespace ValueTypes;

    template <typename Name, typename Type>
    struct PropertyParameter
    {
        using name = Name;
        using type = Type;
    };

    template <typename Name, typename... Parameters>
    struct KnownProperty
    {
        using name = Name;
        using parameters = std::tuple <Parameters...>;

        bool matches(std::string const& str) const
        {
            return std::string(name::c_str) == str;
        }

        std::map <std::string, std::unique_ptr <Value> > valueify (std::vector <std::string> const& raw)
        {
        }
    };

    #define _WCSS_DEFINE_PARAMETER(NAME, DATA) \
        PropertyParameter <STRING(NAME), DATA>

    using KnownPropertyList = std::tuple <
        // Color Properties
        KnownProperty <SHORT_STRING("color"),
            PropertyParameter <STRING("color"), Color>
        >,
        KnownProperty <SHORT_STRING("opacity"),
            PropertyParameter <STRING("opacity"), Numerical>
        >,

        // Background Properties
        KnownProperty <SHORT_STRING("background"),
            PropertyParameter <STRING("background-color"), Color>,
            PropertyParameter <STRING("background-image"), Url>,
            PropertyParameter <STRING("background-position"), Position <true>>,
            PropertyParameter <STRING("background-size"), Point>,
            PropertyParameter <STRING("background-repeat"), Keyword <SHORT_STRING("repeat"),
                                                                  SHORT_STRING("repeat-x"),
                                                                  SHORT_STRING("repeat-y"),
                                                                  SHORT_STRING("no-repeat")>>,
            PropertyParameter <STRING("background-origin"), Keyword <SHORT_STRING("padding-box"),
                                                                     SHORT_STRING("border-box"),
                                                                     SHORT_STRING("content-box")>>,
            PropertyParameter <STRING("background-clip"), Keyword <SHORT_STRING("padding-box"),
                                                                   SHORT_STRING("border-box"),
                                                                   SHORT_STRING("content-box")>>,
            PropertyParameter <STRING("background-attachment"), Keyword <SHORT_STRING("scroll"),
                                                                         SHORT_STRING("fixed"),
                                                                         SHORT_STRING("local")>>
        >
    >;

} // namespace WretchedCss
