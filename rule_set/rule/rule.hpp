#pragma once

#include "property/property.hpp"
#include "selector.hpp"

namespace WretchedCss
{
    struct Rule
    {
        Selector selector;
        std::vector <Property> properties;
    };
} // namespace WretchedCss
