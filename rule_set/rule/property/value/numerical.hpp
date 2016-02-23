#pragma once

#include "../value.hpp"

namespace WretchedCss { namespace ValueTypes
{
    struct Numerical : public Value
    {
        double value;

        Numerical() = default;
        Numerical(double value);
    };

} // namespace ValueTypes
} // namespace WretchedCss
