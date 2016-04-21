#pragma once

#include "rule/rule.hpp"

#include <boost/optional.hpp>

#include <string>
#include <vector>
#include <exception>

namespace WretchedCss
{
    struct RuleSet
    {
        std::vector <Rule> rules;

        RuleSet() = default;
        RuleSet(std::string const& css);

        /**
         * @brief operator [] Returns a Rule by selector, or an empty rule, if the selector was not found.
         * @param selector A css selector, such as "#id" or ".class"
         * @return A rule or an empty rule, if the selector was not found.
         */
        Rule operator[](std::string const& selector) const;
        void eraseRule(std::string const& selector);

        void fromCss(std::string const& css);
        std::string toCss(std::string const& lineBreak = "\n", bool curlyInNextLine = false, bool spacesInsteadOfTabs = true);
        void addCss(std::string const& css);
    };
} // namespace WretchedCss

