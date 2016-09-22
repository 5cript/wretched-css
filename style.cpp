#include "style.hpp"

#include "style_sheet.hpp"

namespace WretchedCss
{
//#####################################################################################################################
    Style::Style(Rule rule)
        : rule_(std::move(rule))
        , parent_(nullptr)
    {
	}
//---------------------------------------------------------------------------------------------------------------------
	Style::Style()
		: rule_()
		, parent_(nullptr)
	{

    }
//---------------------------------------------------------------------------------------------------------------------
    Rule Style::getCombined() const
    {
        if (!hasParent())
            return rule_;

        Rule combined = parent_->getCombined();

        for (auto const& i : rule_.properties)
        {
            if (i.values.empty())
				continue;

			if (!i.values[0])
				continue;

            if (i.values[0]->toString() == "inherit")
                continue;

            combined.addProperty(i);
        }

        return combined;
    }
//---------------------------------------------------------------------------------------------------------------------
    bool Style::hasParent() const
    {
        return parent_ != nullptr;
    }
//---------------------------------------------------------------------------------------------------------------------
    Style& Style::derive(Style const* parent)
    {
		parent_ = parent;
		return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    Style Style::mergeInlineCss(std::string const& inlineCss) const
    {
        StyleSheet sheet(std::string("#INLINE {") + inlineCss + "}");
        auto inli = sheet.select("#INLINE").get(); // cannot be boost::none - impossible!
        inli.derive(this);
        return inli.getCombined();
    }
//---------------------------------------------------------------------------------------------------------------------
    Rule Style::getRule() const
    {
        return rule_;
    }
//#####################################################################################################################
}
