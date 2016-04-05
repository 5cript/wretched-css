#pragma once

#include "../value.hpp"
#include "numerical.hpp"

namespace WretchedCss { namespace ValueTypes
{
    struct Point : public Value
    {
        NumericValue left;
        NumericValue top;

        std::string getTypeString() const override;
        std::string toString() const override;
        Point() = default;
        Point(NumericValue left, NumericValue top);
    };

} // namespace ValueTypes
} // namespace WretchedCss
