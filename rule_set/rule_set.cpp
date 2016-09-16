#include "rule_set.hpp"

#ifndef __BORLANDC__
#	include "twisted-spirit/core/parse.hpp"
#
#	include "../parser/rule_set.hpp"
#	include "../parser/comment.hpp"
#	include "../parser/property.hpp"
#endif

#include "rule/property/value/keyword.hpp"
#include "rule/property/value/numerical.hpp"
#include "rule/property/value/dimensionless.hpp"
#include "rule/property/value/string.hpp"
#include "rule/property/value/url.hpp"
#include "rule/property/value/point.hpp"
#include "rule/property/value/color.hpp"

#ifndef Q_MOC_RUN
#   include "SimpleJSON/parse/jsd.hpp"
#   include "SimpleJSON/parse/jsd_convenience.hpp"
#   include "SimpleJSON/stringify/jss.hpp"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#   include "SimpleJSON/utility/polymorphy.hpp"
#endif // Q_MOC_RUN

#include <sstream>

JSON_DECLARE_POLYMORPHIC
(
    WretchedCss::Value,
    (WretchedCss::ValueTypes::NumericValue)
    // (WretchedCss::ValueTypes::Keyword)
    (WretchedCss::ValueTypes::DimensionlessValue)
    (WretchedCss::ValueTypes::StringValue)
    (WretchedCss::ValueTypes::Url)
    (WretchedCss::ValueTypes::Point)
    (WretchedCss::ValueTypes::Color)
)

#include <boost/algorithm/string.hpp>

#include <stdexcept>
#include <sstream>
#include <iostream>

namespace WretchedCss
{
//#####################################################################################################################
    std::string removeComments(std::string const& str)
	{
#ifndef __BORLANDC__
		std::string result;

		using namespace TwistedSpirit;

		TYPEDEF_GRAMMAR(css_comment_remover);
		auto stripped = parse<grammar>(str);

		// cannot fail
		return stripped.second;
#else
		return "__BORLANDC__ DEFINED";
#endif
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
#ifndef __BORLANDC__
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
#endif
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
//---------------------------------------------------------------------------------------------------------------------
    void RuleSet::fromJson(std::string const& json)
    {
        auto tree = JSON::parse_json(json);
        JSON::parse(rules, "style", tree);
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string RuleSet::toJson() const
    {
        std::stringstream sstr;
        sstr << '{';
        JSON::stringify(sstr, "stream", rules, JSON::ProduceNamedOutput);
        sstr << '}';
        return sstr.str();
    }
//#####################################################################################################################
} // namespace WretchedCss
