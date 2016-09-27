#pragma once

#include "../value.hpp"

namespace WretchedCss { namespace ValueTypes
{
    struct DimensionlessValue : public Value
                              , JSON::Stringifiable <DimensionlessValue>
                              , JSON::Parsable <DimensionlessValue>
    {
        double value;

        std::string toString() const override;
        std::string getTypeString() const override;
        DimensionlessValue* clone() const override;

        DimensionlessValue() = default;
        DimensionlessValue(double value);
    };

} // namespace ValueTypes
} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::ValueTypes::DimensionlessValue,
    (double, value)
)
