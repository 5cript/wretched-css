#include "style_sheet.hpp"

#include <utility>
#include <map>
#include <iterator>

namespace WretchedCss
{
//#####################################################################################################################
    StyleSheet::StyleSheet(RuleSet const& ruleSet)
        : styles_()
        , pxPerEm_(16)
    {
        for (auto const& i : ruleSet.rules)
            styles_.push_back({i});
    }
//---------------------------------------------------------------------------------------------------------------------
    unsigned long StyleSheet::getPxPerEm() const
    {
        return pxPerEm_;
    }
//---------------------------------------------------------------------------------------------------------------------
    void StyleSheet::setPxPerEm(unsigned long pxPerEm)
    {
        pxPerEm_ = pxPerEm;
    }
//---------------------------------------------------------------------------------------------------------------------
    StyleSheet::StyleSheet(std::string const& css)
        : StyleSheet(RuleSet(css))
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    boost::optional <Style> StyleSheet::getByClass(std::string const& clas)
    {
        return select(std::string(".") + clas);
    }
//---------------------------------------------------------------------------------------------------------------------
    boost::optional <Style> StyleSheet::getById(std::string const& id)
    {
        return select(std::string("#") + id);
    }
//---------------------------------------------------------------------------------------------------------------------
    boost::optional <Style> StyleSheet::getByType(std::string const& type) const
    {
        return select(type);
    }
//---------------------------------------------------------------------------------------------------------------------
    boost::optional <Style> StyleSheet::select(std::string const& selector, bool cascade) const
    {
        std::multimap <long, std::pair <int, Style> > filtered;
        int counter = 0;
        for (auto const& i : styles_)
        {
            long specificity = i.getRule().selector.getHighestSpecificityFor(selector);
            if (specificity != -1)
                filtered.insert(std::pair <long, std::pair <int, Style>> (specificity, {counter, i}));
            ++counter;
        }

        if (filtered.empty())
            return boost::none;

        Style combined = filtered.rbegin()->second.second;
        Style* last = &combined;
        for (auto front = filtered.rbegin(), end = filtered.rend(), i = std::next(front); i != end; ++i)
        {
            last->derive(&i->second.second);
            last = &i->second.second;
        }

        return boost::optional <WretchedCss::Style> {combined.getCombined()};
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string StyleSheet::toString() const
    {
        RuleSet set;
        for (auto const& i : styles_)
        {
            set.rules.push_back(i.getRule());
        }
        return set.toCss();
    }
//#####################################################################################################################
}
