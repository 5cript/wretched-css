#pragma once

#include "../value.hpp"

namespace WretchedCss { namespace ValueTypes
{
    struct StringValue : public Value
    {
        std::string value;
        StringValue(std::string value);

        std::string toString() const override;
        std::string getTypeString() const override;
        StringValue* clone() const override;
    };

} // namespace ValueTypes
} // namespace WretchedCss
