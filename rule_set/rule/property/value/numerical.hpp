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
    enum class Unit
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
    struct NumericValue : public Value
    {
        Unit unit;
        double value;

        std::string getTypeString() const override;
        NumericValue(Unit unit = Unit::px, double value = 0.);
    };

    /**
     *  Tries to convert the string into a NumericValue value object.
     */
    boost::optional <NumericValue> tryGetNumericValueFromString(std::string const& str);

    /**
     *  Converts a string into an enum value.
     *
     *  @param unit A unit as a string, such as "px".
     *  @return Returns a unit as the enum value.
     */
    Unit getUnitFromString(std::string const& unit);

    /**
     *  Converts a unit enum value into a string.
     *
     *  @param unit A unit as an enum value, such as "px".
     *  @return Returns a unit as a string.
     */
    std::string unitToString(Unit unit);

} // namespace ValueTypes
} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::ValueTypes::NumericValue,
    unit, value
)
