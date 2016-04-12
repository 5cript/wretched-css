#pragma once

#include "../value.hpp"

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/optional.hpp>

#include <string>
#include <cstdint>

namespace WretchedCss { namespace ValueTypes
{
    // This is an intermediate, not intended for external use
    struct HslColor
    {
        uint16_t h;
        double s;
        double l;
        double a;
    };

    /**
     *  RGBA color. 24bit + alpha.
     */
    struct Color : public Value
    {
        std::string originalString;

        uint8_t r;
        uint8_t g;
        uint8_t b;
        double a;

        std::string toString() const override;
        std::string getTypeString() const override;
        Color* clone() const override;

        Color(uint8_t r, uint8_t g, uint8_t b, double a);
        Color() = default;
    };

    Color colorFromString(std::string const& color);
    boost::optional <Color> tryGetColorFromString(std::string const& color);

} // namespace ValueTypes
} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::ValueTypes::HslColor,
    h, s, l, a
)

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::ValueTypes::Color,
    r, g, b, a
)
