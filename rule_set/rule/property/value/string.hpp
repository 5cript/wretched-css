#pragma once

#include "../value.hpp"

namespace WretchedCss { namespace ValueTypes
{
    struct StringValue : public Value
                       , public JSON::Stringifiable <StringValue>
                       , public JSON::Parsable <StringValue>
    {
        std::string value;
        StringValue(std::string value);
        StringValue();

        std::string toString() const override;
        std::string getTypeString() const override;
        StringValue* clone() const override;
    };

} // namespace ValueTypes
} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::ValueTypes::StringValue,
    (std::string, value)
)
