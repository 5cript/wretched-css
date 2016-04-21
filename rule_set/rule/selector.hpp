#pragma once

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

    struct ParsedSelector
    {
        SelectorType type;
        std::string selectorString;
        std::vector <std::string> classes;
        std::vector <std::string> filters; // +element, >element, ~element, element, :active, ::before, ::nth-child(), ::lang()

        std::string toString() const;
        long calculateSpecificity() const;
        bool canSelect(std::string const& selector) const;
    };

    struct Selector
    {
    public:
        Selector() = default;
        Selector(std::string const& raw);

        std::string toString() const;
        std::vector <ParsedSelector> getSelectors() const;

        // returns -1, if cannot be selected.
        long getHighestSpecificityFor(std::string const& selector);
    private:
        std::vector <ParsedSelector> selectors_;
    };
} // namespace WretchedCss


BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::ParsedSelector,
    type, selectorString, filters, classes
)
