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
    };
} // namespace WretchedCss

