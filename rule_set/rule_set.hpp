#pragma once

#include "rule/rule.hpp"

#include <vector>
#include <vector>

namespace WretchedCss
{
    struct RuleSet
    {
        std::vector <Rule> rules;

        void fromCss(std::string const& css);
        std::string toCss(std::string const& lineBreak = "\n", bool curlyInNextLine = false, bool spacesInsteadOfTabs = true);
    };
} // namespace WretchedCss

