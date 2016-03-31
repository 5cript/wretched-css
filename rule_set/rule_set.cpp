#include "rule_set.hpp"

#include "twisted-spirit/core/parse.hpp"

#include "../parser/rule_set.hpp"
#include "../parser/comment.hpp"
#include "../parser/property.hpp"

#include <stdexcept>
#include <iostream>

namespace WretchedCss
{
//#####################################################################################################################
    std::string removeComments(std::string const& str)
    {
        std::string result;

        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(css_comment_remover);
        auto stripped = parse<grammar>(str);

        // cannot fail
        return stripped.second;
    }
//#####################################################################################################################
    void RuleSet::fromCss(std::string const& css)
    {
        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(rule_set_grammar);
        auto intermediate = parse<grammar>(removeComments(css));

        if (intermediate.first == ParsingResult::FAIL)
            throw std::invalid_argument("Not a valid css file");

        for (auto const& i : intermediate.second)
        {
            Rule rule;

            // rule-level
            rule.selector.selector = i.selector;
            for (auto const& prop : i.declarations)
            {
                // property-level
                rule.properties.push_back(std::move(parseProperty(prop)));
            }

            rules.push_back(std::move(rule));
        }
    }
//#####################################################################################################################
} // namespace WretchedCss
