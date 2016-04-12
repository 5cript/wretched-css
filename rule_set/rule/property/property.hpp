#pragma once

#include "value.hpp"

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
    struct Property
    {
        Property() = default;

        std::string key;
        std::vector <std::unique_ptr <Value> > values;

        Property& operator=(Property const& property);
        Property(Property const& property);
    };

} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::RawProperty,
    key, values
)
