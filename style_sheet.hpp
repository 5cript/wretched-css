#pragma once

#include "rule_set/rule_set.hpp"
#include "style.hpp"

#include <boost/optional.hpp>

namespace WretchedCss
{
    class StyleSheet
    {
    public:
        StyleSheet(RuleSet const& ruleSet);

        /**
         *  Creates a style sheet from a CSS formatted string.
         */
        StyleSheet(std::string const& css);

        /**
         *  Returns the conversion factor for em <-> px.
         *
         *  @return 1em = ?px
         */
        unsigned long getPxPerEm() const;

        /**
         *  Sets the conversion factor for em <-> px.
         *
         *  @param pxPerEm 1em = ?px
         */
        void setPxPerEm(unsigned long pxPerEm);

        /**
         *  Get the style by class. ".class" selection.
         *
         *  @param clas The class to search. Omit the .
         *
         *  @return A constructed style containing all style properties.
         */
        boost::optional <Style> getByClass(std::string const& clas);

        /**
         *  Get the style by id. "#id" selection.
         *
         *  @param id The id to search. Omit the #
         *
         *  @return A constructed style containing all style properties.
         */
        boost::optional <Style> getById(std::string const& id);

        /**
         *  Get the style by element type. eg. "body".
         *
         *  @param type A type name to search.
         *
         *  @return A constructed style containing all style properties.
         */
        boost::optional <Style> getByType(std::string const& type) const;

        /**
         *  Selects a style by selector. eg. "body, #someid, .class.bla".
		 *  Automatically does inheritance etc.
		 *
		 *	@param selector The selector to select rules with.
		 *	@param cascade Turns of automatic cascadation, if false.
		 */
		boost::optional <Style> select(std::string const& selector, bool cascade = true) const;

        /**
         *  Transforms the style sheet class into a .css text file.
         *
         *  @return CSS formatted string.
         */
        std::string toString() const;

    private:
        std::vector <Style> styles_;
        unsigned long pxPerEm_;
    };
}
