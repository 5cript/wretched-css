#pragma once

#include "property/property.hpp"
#include "selector.hpp"

#include <boost/optional.hpp>

namespace WretchedCss
{
    struct Rule
    {
        Selector selector;
        std::vector <Property> properties;

        void addProperty(Property const& prop);
        boost::optional <Property> operator[](std::string const& propertyName) const;
    };
} // namespace WretchedCss
