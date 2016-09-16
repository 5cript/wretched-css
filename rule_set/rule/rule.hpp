#pragma once

#include "property/property.hpp"
#include "selector.hpp"

#include <boost/optional.hpp>

#include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#include "SimpleJSON/parse/jsd_fusion_adapted_struct.hpp"

namespace WretchedCss
{
    struct Rule : public JSON::Stringifiable <Rule>
                , public JSON::Parsable <Rule>
    {
        Selector selector;
        std::vector <Property> properties;

        void addProperty(Property const& prop);
        boost::optional <Property> operator[](std::string const& propertyName) const;
    };
} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::Rule,
    (WretchedCss::Selector, selector)
    (std::vector <WretchedCss::Property>, properties)
)
