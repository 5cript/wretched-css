#pragma once

#include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#include "SimpleJSON/parse/jsd_fusion_adapted_struct.hpp"

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <string>
#include <vector>

namespace WretchedCss
{
    enum class SelectorType
    {
        Element,
        Classes,
        Id,
        All,
        Attribute
    };

    struct ParsedSelector : public JSON::Stringifiable <ParsedSelector>
                          , public JSON::Parsable <ParsedSelector>
    {
		SelectorType type;
		std::string selectorString;
		std::vector <std::string> classes;
		std::vector <std::string> filters; // +element, >element, ~element, element, :active, ::before, ::nth-child(), ::lang()

        std::string toString() const;
        long calculateSpecificity() const;
        bool canSelect(std::string const& selector) const;
    };

    class Selector : public JSON::Stringifiable <Selector>
                   , public JSON::Parsable <Selector>
    {
    public:
        Selector() = default;
        Selector(std::string const& raw);

        std::string toString() const;
        std::vector <ParsedSelector> getSelectors() const;

        // returns -1, if cannot be selected.
        long getHighestSpecificityFor(std::string const& selector);

    //private:
    public: // this is necessary, is not worth the effort to fix
        std::vector <ParsedSelector> selectors_;
    };
} // namespace WretchedCss


BOOST_FUSION_ADAPT_STRUCT
(
	WretchedCss::ParsedSelector,
	(WretchedCss::SelectorType, type)
	(std::string, selectorString)
	(std::vector <std::string>, filters)
	(std::vector <std::string>, classes)
)

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::Selector,
    (std::vector <WretchedCss::ParsedSelector>, selectors_)
)
