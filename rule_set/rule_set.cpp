#include "rule_set.hpp"

#include "twisted-spirit/core/parse.hpp"

#include "../parser/rule_set.hpp"
#include "../parser/comment.hpp"
#include "../parser/property.hpp"

#include <boost/algorithm/string.hpp>

#include <stdexcept>
#include <sstream>
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
    Rule RuleSet::operator[](std::string const& selector) const
    {
        for (auto const& rule : rules)
            if (selector == rule.selector.toString())
                return rule;

        return {};
    }
//---------------------------------------------------------------------------------------------------------------------
    void RuleSet::eraseRule(std::string const& selector)
    {
        rules.erase(std::remove_if(rules.begin(), rules.end(), [&](decltype(rules)::value_type const& rule){
            return rule.selector.toString() == selector;
        }), rules.end());
    }
//---------------------------------------------------------------------------------------------------------------------
    void RuleSet::fromCss(std::string const& css)
    {
        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(rule_set_grammar);
        auto intermediateRuleSet = parse<grammar>(removeComments(css));

        if (intermediateRuleSet.first == ParsingResult::FAIL)
            throw std::invalid_argument("Not a valid css file");

        for (auto const& i : intermediateRuleSet.second)
        {
            Rule rule;

            // rule-level
            rule.selector = {i.selector};

            for (auto const& prop : i.declarations)
            {
                // property-level
                rule.properties.push_back(parseProperty(prop));
            }

            rules.push_back(std::move(rule));
        }
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string RuleSet::toCss(std::string const& lineBreak, bool curlyInNextLine, bool spacesInsteadOfTabs)
    {
        std::stringstream sstr;

        for (auto const& i : rules)
        {
            sstr << i.selector.toString();

            if (curlyInNextLine)
                sstr << lineBreak <<'{';
            else
                sstr << " {";
            sstr << lineBreak;

            for (auto const& p : i.properties)
            {
                if (spacesInsteadOfTabs)
                    sstr << "    ";
                else
                    sstr << '\t';

                sstr << p.key << ":";
                for (auto const& value : p.values)
                {
                    sstr << ' ' << value->toString();
                }
                sstr << ';' << lineBreak;
            }
            sstr << '}' << lineBreak << lineBreak;
        }
        return sstr.str();
    }
//---------------------------------------------------------------------------------------------------------------------
    RuleSet::RuleSet(std::string const& css)
        : rules()
    {
        fromCss(css);
    }
//---------------------------------------------------------------------------------------------------------------------
    void RuleSet::addCss(std::string const& css)
    {
        RuleSet newSet;
        newSet.fromCss(css);

        for (auto const& i : newSet.rules)
            rules.push_back(std::move(i));
    }
//#####################################################################################################################
} // namespace WretchedCss
