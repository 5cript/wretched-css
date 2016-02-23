#pragma once

#include "../value.hpp"
#include "size.hpp"

namespace WretchedCss { namespace ValueTypes
{
    struct Point : public Value
    {
        Size left;
        Size top;

        Point() = default;
        Point(Size left, Size top);
    };

} // namespace ValueTypes
} // namespace WretchedCss
