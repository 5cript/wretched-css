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
#include <set>

namespace WretchedCss
{
    using namespace ValueTypes;

    template <typename Name, typename Type>
    struct PropertyParameter
    {
        using name = Name;
        using type = Type;
    };

    template <std::size_t Index, typename T, typename... Parameters>
    struct TryValueConversion
    {
        static std::pair <std::string, std::unique_ptr <Value> >
            convert(std::vector <RawValue>::const_iterator& begin,
                    std::vector <RawValue>::const_iterator end,
                    std::set <std::size_t>& blacklist)
        {
            if (blacklist.find(Index))
                return TryValueConversion <Index + 1, Parameters...>::convert(begin, end);

            std::unique_ptr <Value> v = Valueifier <typename T::type>::create(begin, end);

            if (v.get())
            {
                if (!begin->isExtended)
                    blacklist.insert(Index);

                return
                {
                    std::string(T::name::c_str),
                    std::move(v)
                };
            }
            else
                return TryValueConversion <Index + 1, Parameters...>::convert(begin, end);
        }
    };

    template <std::size_t Index, typename T>
    struct TryValueConversion <Index, T>
    {
        static std::pair <std::string, std::unique_ptr <Value>>
            convert(std::vector <RawValue>::const_iterator& begin,
                    std::vector <RawValue>::const_iterator end,
                    std::set <std::size_t>& blacklist)
        {
            if (blacklist.find(Index))
                return {"", nullptr};

            std::unique_ptr <Value> v = Valueifier <typename T::type>::create(begin, end);

            if (v.get() && !begin->isExtended)
                blacklist.insert(Index);

            return
            {
                std::string(T::name::c_str),
                std::move(v)
            };
        }
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

        std::map <std::string, std::unique_ptr <Value> > valueify (std::vector <RawValue> const& raw)
        {
            std::set <std::size_t> alreadySpecifiedParameters;

            auto begin = std::begin(raw);
            auto end = std::end(raw);

            std::map <std::string, std::unique_ptr <Value> > parameters;

            while (begin != end)
            {
                auto result = TryValueConversion <0, Parameters...>::convert(begin, end, alreadySpecifiedParameters);
                if (!result.second.get())
                    throw std::runtime_error((std::string("raw parameters contain an unexpected one.") + begin->data).c_str());

                parameters[result.first] = std::move(result.second);
            }

            return parameters;
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
