#pragma once

#include "../value.hpp"

#include "mplex/string/string.hpp"

#include <cstring>

namespace WretchedCss { namespace ValueTypes
{
    template <typename T, typename... List>
    struct ValidKeywords
    {
        static constexpr bool isKeyword(std::string const& rhs)
        {
            return rhs == std::string(T::c_str) ? true : ValidKeywords <List...>::isKeyword(rhs);
        }
    };

    template <typename T>
    struct ValidKeywords <T>
    {
        static constexpr bool isKeyword(std::string const& rhs)
        {
            return std::string(T::c_str) == rhs;
        }
    };

    template <typename... Keywords>
    struct Keyword : public Value
    {
        using keywords = ValidKeywords <Keywords...>;

        std::string value;

        bool verify() const
        {
            return keywords::isKeyword(value);
        }

        std::string getTypeString() const override
        {
            return "Keyword";
        }

        Keyword(std::string const& value)
            : value(value)
        {
        }
    };

} // namespace ValueTypes
} // namespace WretchedCss
