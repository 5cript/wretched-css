#pragma once

#include "../value.hpp"

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/optional.hpp>

#include <string>
#include <cstdint>

namespace WretchedCss { namespace ValueTypes
{
    // Source: http://www.w3schools.com/cssref/css_units.asp
    // WARNING: MODIFY SOURCE IF YOU DO CHANGES TO THIS! AND PARSER
    enum class SizeUnit
    {
        em, ex, percent, px, cm, mm, in, pt, pc,
        ch,
        rem,
        vh, vw,
        vmin,
        vmax
    };

    /**
     *  Holds values like 10px, 2em, 12.5%
     */
    struct Size : public Value
    {
        SizeUnit unit;
        double value;
    };

    /**
     *  Tries to convert the string into a Size value object.
     */
    boost::optional <Size> tryGetSizeFromString(std::string const& str);

    /**
     *  Converts a string into an enum value.
     *
     *  @param unit A unit as a string, such as "px".
     *  @return Returns a unit as the enum value.
     */
    SizeUnit getUnitFromString(std::string const& unit);

    /**
     *  Converts a unit enum value into a string.
     *
     *  @param unit A unit as an enum value, such as "px".
     *  @return Returns a unit as a string.
     */
    std::string unitToString(SizeUnit unit);

} // namespace ValueTypes
} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::ValueTypes::Size,
    unit, value
)
