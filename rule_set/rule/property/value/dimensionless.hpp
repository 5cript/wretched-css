#pragma once

#include "../value.hpp"

namespace WretchedCss { namespace ValueTypes
{
    struct DimensionlessValue : public Value
    {
        double value;

        std::string getTypeString() const override;
        DimensionlessValue() = default;
        DimensionlessValue(double value);
    };

} // namespace ValueTypes
} // namespace WretchedCss
