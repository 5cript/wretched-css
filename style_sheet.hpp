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
        boost::optional <Style> getByType(std::string const& type);

        /**
         *  Selects a style by selector. eg. "body, #someid, .class.bla".
         *  Automatically does inheritance etc.
         */
        boost::optional <Style> select(std::string const& selector);

        /**
         *  Transforms the style sheet class into a .css text file.
         *
         *  @return CSS formatted string.
         */
        std::string toString() const;

    private:
        std::vector <Style> styles_;
    };
}
