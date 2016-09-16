#pragma once

#include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#include "SimpleJSON/parse/jsd_fusion_adapted_struct.hpp"

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <string>

namespace WretchedCss
{
    struct RawValue
    {
        std::string data = "";
        // comma separated lists: url(bla.jpg), url(blub.jpg) black
        //                                 yes,           yes    no
        bool isExtended = false;
    };

    struct Value
    {
        virtual std::string getTypeString() const = 0;
        virtual std::string toString() const = 0;
        virtual Value* clone() const = 0;
        virtual ~Value() = default;
    };

} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::RawValue,
	(std::string, data)
	(bool, isExtended)
)

/*
BOOST_FUSION_ADAPT_STRUCT
(
	WretchedCss::Value
)
*/
