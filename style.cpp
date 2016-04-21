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
    Rule Style::getCombined() const
    {
        if (!hasParent())
            return rule_;

        Rule combined = parent_->getCombined();

        for (auto const& i : rule_.properties)
        {
            if (i.values.empty())
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
    void Style::derive(Style const* parent)
    {
        parent_ = parent;
    }
//---------------------------------------------------------------------------------------------------------------------
    Style Style::mergeInlineCss(std::string const& inlineCss) const
    {
        using namespace std::string_literals;
        StyleSheet sheet("#INLINE {"s + inlineCss + "}"s);
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
