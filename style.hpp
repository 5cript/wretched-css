#pragma once

#include "rule_set/rule_set.hpp"

namespace WretchedCss
{
    class Style
    {
    public:
		Style(Rule rule);
		Style();

        /**
         *  Sets a style as a parent.
         */
        Style& derive(Style const* parent);

        /**
         *  Merge parent.getCombined() and this.
         */
        Rule getCombined() const;

        /**
         *  Does the style have a parent?
         */
        bool hasParent() const;

        /**
         *  Getter for rule_.
         */
        Rule getRule() const;

        /**
         *  Mixes inline css into the style.
         *  inline css has the highest specificity, so that this will derive from the inline css.
         *
         *  @return A new merged style.
         */
        Style mergeInlineCss(std::string const& inlineCss) const;

    private:
        Rule rule_;
        Style const* parent_;
    };
}
