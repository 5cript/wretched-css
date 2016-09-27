#pragma once

#include "../value.hpp"
#include "numerical.hpp"

namespace WretchedCss { namespace ValueTypes
{
    struct Point : public Value
                 , public JSON::Stringifiable <Point>
                 , public JSON::Parsable <Point>
    {
        NumericValue left;
        NumericValue top;

        std::string getTypeString() const override;
        std::string toString() const override;
        Point* clone() const override;

        Point() = default;
        Point(NumericValue left, NumericValue top);
    };

} // namespace ValueTypes
} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::ValueTypes::Point,
    (WretchedCss::ValueTypes::NumericValue, left)
    (WretchedCss::ValueTypes::NumericValue, top)
)
