#pragma once

#include "../value.hpp"

namespace WretchedCss { namespace ValueTypes
{
    struct StringValue : public Value
    {
        std::string value;
    };

} // namespace ValueTypes
} // namespace WretchedCss
