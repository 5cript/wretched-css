#pragma once

#include "value.hpp"

#include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#include "SimpleJSON/parse/jsd_fusion_adapted_struct.hpp"

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <string>
#include <vector>
#include <memory>

namespace WretchedCss
{
    // This type is solely for parsing.
    struct RawProperty
    {
        std::string key;
        std::vector <RawValue> values;
    };


    // This type is for use, after parsing and preprocessing.
    struct Property : public JSON::Stringifiable <Property>
                    , public JSON::Parsable <Property>
    {
        Property() = default;
        Property(std::string key, std::vector <std::unique_ptr <Value>> const& values);

        std::string key;
        std::vector <std::unique_ptr <Value> > values;

        Property& operator=(Property const& property);
        Property(Property const& property);
    };

} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::RawProperty,
	(std::string, key)
	(std::vector <WretchedCss::RawValue>, values)
)

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::Property,
    (std::string, key)
    (std::vector <std::unique_ptr <WretchedCss::Value> >, values)
)
