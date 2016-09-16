#pragma once

#include "../value.hpp"

#include <boost/optional.hpp>

namespace WretchedCss { namespace ValueTypes
{
    struct Url : public Value
               , public JSON::Stringifiable <Url>
               , public JSON::Parsable <Url>
    {
        std::string value;

        std::string getTypeString() const override;
        std::string toString() const override;
        Url* clone() const override;

        Url() = default;
        Url(std::string value);
    };

    boost::optional <Url> tryGetUrlFromString(std::string const& str);

} // namespace ValueTypes
} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::ValueTypes::Url,
    (std::string, value)
)
