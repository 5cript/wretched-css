#pragma once

#include "../value.hpp"

namespace WretchedCss { namespace ValueTypes
{
    struct StringValue : public Value
    {
        std::string value;

        std::string getTypeString() const override;
    };

} // namespace ValueTypes
} // namespace WretchedCss
