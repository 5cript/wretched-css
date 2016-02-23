#pragma once

#include "../value.hpp"
#include "size.hpp"

namespace WretchedCss { namespace ValueTypes
{
    template <bool RequireSlash>
    struct Position : public Value
    {
        enum : bool {
            requireSlash = RequireSlash
        };

        Size left;
        Size top;

        Position (Size left, Size top)
            : left(std::move(left))
            , top(std::move(top))
        {
        }
        Position() = default;
    };

} // namespace ValueTypes
} // namespace WretchedCss

