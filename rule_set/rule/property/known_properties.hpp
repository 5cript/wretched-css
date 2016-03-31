#pragma once

#include "valueifier.hpp"

#include "value.hpp"

#define HAS_BOOST_STRING_ALGORITHM
#include "mplex/tuple/apply.hpp"
#include "mplex/fundamental/null_type.hpp"

#include "mplex/string/string.hpp"
#include "mplex/string/inline_string.hpp"
#include "mplex/type_print/type_print.hpp"

#include <tuple>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <set>
#include <iostream>

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
            // continue if blacklisted
            if (blacklist.find(Index) != std::end(blacklist))
                return TryValueConversion <Index + 1, Parameters...>::convert(begin, end, blacklist);

            //std::cout << "try "; mplex::print_single_decluttered <typename T::type>() << "\n";
            //std::cout << "on " << begin->data << "\n\n";

            // try valueification
            std::unique_ptr <Value> v {Valueifier <typename T::type>::create(begin, end)};

            // did it succeed?
            if (v.get())
            {
                if (!begin->isExtended)
                    blacklist.insert(Index);

                //std::cout << "Found: "; mplex::print_single_decluttered <typename T::type>() << "\n";

                return
                {
                    std::string(T::name::c_str),
                    std::move(v)
                };
            }
            else // no -> try next
                return TryValueConversion <Index + 1, Parameters...>::convert(begin, end, blacklist);
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
            if (blacklist.find(Index) != std::end(blacklist))
                return {"", nullptr};

            std::unique_ptr <Value> v {Valueifier <typename T::type>::create(begin, end)};

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

        static bool matches(std::string const& str)
        {
            return std::string(name::c_str) == str;
        }

        static std::map <std::string, std::unique_ptr <Value> > valueify (std::vector <RawValue> const& raw)
        {
            std::set <std::size_t> alreadySpecifiedParameters;

            auto begin = std::begin(raw);
            auto end = std::end(raw);

            std::map <std::string, std::unique_ptr <Value> > parameters;

            while (begin != end)
            {
                auto result = TryValueConversion <0, Parameters...>::convert(begin, end, alreadySpecifiedParameters);
                if (!result.second.get())
                    throw std::runtime_error((std::string("raw parameters contain an unexpected one: ") + begin->data).c_str());

                parameters[result.first] = std::move(result.second);
            }

            return parameters;
        }
    };

    #define _WCSS_DEFINE_PARAMETER(NAME, DATA) \
        PropertyParameter <STRING(NAME), DATA>

    using KnownPropertyList = std::tuple <
        // Alignment
        KnownProperty <SHORT_STRING("align-content"),
            PropertyParameter <STRING("align-content"), Keyword <SHORT_STRING("stretch"),
                                                                 SHORT_STRING("center"),
                                                                 SHORT_STRING("flex-start"),
                                                                 SHORT_STRING("flex-end"),
                                                                 SHORT_STRING("space-between"),
                                                                 SHORT_STRING("space-around")>>
        >,
        KnownProperty <SHORT_STRING("align-items"),
            PropertyParameter <STRING("align-items"), Keyword <SHORT_STRING("stretch"),
                                                               SHORT_STRING("center"),
                                                               SHORT_STRING("flex-start"),
                                                               SHORT_STRING("flex-end"),
                                                               SHORT_STRING("baseline")>>
        >,
        KnownProperty <SHORT_STRING("align-self"),
            PropertyParameter <STRING("align-self"), Keyword <SHORT_STRING("auto"),
                                                              SHORT_STRING("stretch"),
                                                              SHORT_STRING("center"),
                                                              SHORT_STRING("flex-start"),
                                                              SHORT_STRING("flex-end"),
                                                              SHORT_STRING("baseline")>>
        >,

        // All
        KnownProperty <SHORT_STRING("all"),
            PropertyParameter <SHORT_STRING("all"), Keyword <SHORT_STRING("unset")>>
        >,

        // Animation
        // ...

        // Backface
        KnownProperty <STRING("backface-visibility"),
            PropertyParameter <STRING("backface-visibility"), Keyword <SHORT_STRING("hidden"),
                                                                       SHORT_STRING("visible")>>
        >,

        // Color Properties
        KnownProperty <SHORT_STRING("color"),
            PropertyParameter <SHORT_STRING("color"), Color>
        >,
        KnownProperty <SHORT_STRING("opacity"),
            PropertyParameter <SHORT_STRING("opacity"), DimensionlessValue>
        >,

        // Background Properties
        KnownProperty <SHORT_STRING("background"),
            PropertyParameter <STRING("background-color"), Color>,
            PropertyParameter <STRING("background-image"), Url>,
            PropertyParameter <STRING("background-position"), Point>,
            PropertyParameter <SHORT_STRING("SLASH"), Keyword <SHORT_STRING("/")>>,
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
        >,
        KnownProperty <STRING("background-attachment"),
            PropertyParameter <STRING("background-attachment"), Keyword <SHORT_STRING("scroll"),
                                                                        SHORT_STRING("fixed"),
                                                                        SHORT_STRING("local")>>
        >,
        KnownProperty <STRING("background-blend-mode"),
			PropertyParameter <STRING("background-blend-mode"), Keyword <SHORT_STRING("normal"),
			                                                             SHORT_STRING("multiply"),
			                                                             SHORT_STRING("screen"),
			                                                             SHORT_STRING("overlay"),
			                                                             SHORT_STRING("darken"),
			                                                             SHORT_STRING("lighten"),
			                                                             SHORT_STRING("color-dodge"),
			                                                             SHORT_STRING("saturation"),
			                                                             SHORT_STRING("color"),
			                                                             SHORT_STRING("luminosity")>>
		>,
        KnownProperty <STRING("background-clip"),
            PropertyParameter <STRING("background-clip"), Keyword <SHORT_STRING("padding-box"),
                                                                   SHORT_STRING("border-box"),
                                                                   SHORT_STRING("content-box")>>
        >,
        KnownProperty <STRING("background-color"),
            PropertyParameter <STRING("background-color"), Color>
        >,
        KnownProperty <STRING("background-image"),
            PropertyParameter <STRING("background-image"), Url>
        >,
        KnownProperty <STRING("background-origin"),
			PropertyParameter <STRING("background-origin"), Keyword <SHORT_STRING("padding-box"),
			                                                         SHORT_STRING("border-box"),
			                                                         SHORT_STRING("content-box")>>
		>,
		KnownProperty <STRING("background-position"),
            PropertyParameter <STRING("background-position"), Point>
        >,
        KnownProperty <STRING("background-repeat"),
			PropertyParameter <STRING("background-repeat"), Keyword <SHORT_STRING("repeat"),
			                                                         SHORT_STRING("repeat-x"),
			                                                         SHORT_STRING("repeat-y"),
			                                                         SHORT_STRING("no-repeat")>>
		>,
        KnownProperty <STRING("background-size"),
            PropertyParameter <STRING("background-size"), Point>
        >,

        // Border
        //KnownProperty <SHORT_STRING("border"),
        //    PropertyParameter <SHORT_STRING("border-width"),
    >;

    template <typename T, typename... List>
    struct ValueifyPropertyImpl
    {
        static std::map <std::string, std::unique_ptr <Value> > convert(
            std::string const& what,
            std::vector <RawValue> const& raw
        )
        {
            if (T::matches(what))
                return T::valueify(raw);
            else
                return ValueifyPropertyImpl <List...>::convert(what, raw);
        }
    };

    template <typename T>
    struct ValueifyPropertyImpl <T>
    {
        static std::map <std::string, std::unique_ptr <Value> > convert(
            std::string const& what,
            std::vector <RawValue> const& raw
        )
        {
            if (T::matches(what))
                return T::valueify(raw);
            else
                return {};
        }
    };

    struct ValueifyProperty
    {
        static std::map <std::string, std::unique_ptr <Value> > convert(
            std::string const& what,
            std::vector <RawValue> const& raw
        )
        {
            return mplex::apply_t <KnownPropertyList, ValueifyPropertyImpl>::convert(what, raw);
        }
    };

} // namespace WretchedCss
