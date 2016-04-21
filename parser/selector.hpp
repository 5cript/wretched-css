#pragma once

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/rules/space.hpp"
#include "twisted-spirit/grammars/unescaped_string.hpp"

#include <vector>
#include <string>

namespace WretchedCss
{
    using namespace TwistedSpirit;

    namespace Internal
    {
        std::string selectorToString(ParsedSelector const& ps)
        {
            return ps.toString();
        }
    }

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct selector_grammar : qi::grammar <Iterator, std::vector <ParsedSelector>()>
    {
        using grammar_result = std::vector <ParsedSelector>;

        selector_grammar() : selector_grammar::base_type(main, "selector_split")
        {
            using namespace common_usings;
            INSTALL_ERROR_HANDLER;
            INSTALL_WARNING_HANDLER;

            identifier =
               +(
                    (
                        // escapes
                            qi::char_('\\')
                        >> (qi::char_ - blank)          [phoenix::push_back(_val, qi::_1)]
                    )
                    |
                    (
                            qi::char_("-_")
                        |   qi::alnum
                    )                                   [phoenix::push_back(_val, qi::_1)]
                )
            ;

            value %=
                    identifier
                |   escape_string
            ;

            selector_type =
                    qi::char_('#')                  [_val = SelectorType::Id]
                |   eps                             [_val = SelectorType::Element]
            ;

            attributeSelector =
                    qi::char_('[')                  [at_c <0> (_val) = SelectorType::Attribute, at_c <1> (_val) = "["]
                >>  identifier                      [at_c <1> (_val) += qi::_1]
                >> -(
                            (
                                    qi::lit("=")    [at_c <1> (_val) += "="]
                                |   qi::lit("~=")   [at_c <1> (_val) += "~="]
                                |   qi::lit("|=")   [at_c <1> (_val) += "|="]
                                |   qi::lit("^=")   [at_c <1> (_val) += "^="]
                                |   qi::lit("$=")   [at_c <1> (_val) += "$="]
                                |   qi::lit("*=")   [at_c <1> (_val) += "*="]
                            )
                        >>  value                   [at_c <1> (_val) += qi::_1]
                    )
                >>  qi::char_(']')                  [at_c <1> (_val) += "]"]
            ;

            // :
            fixed_filters.add
                ("active", "active")("checked", "checked")("disabled", "disabled")("enabled", "enabled")
                ("empty", "empty")("enabled", "enabled")("first-child", "first-child")
                ("first-of-type", "first-of-type")("focus", "focus")
                ("hover", "hover")("in-range", "in-range")("invalid", "invalid")
                ("last-child", "last-child")("last-of-type", "last-of-type")
                ("link", "link")("only-of-type", "only-of-type")
                ("only-child", "only-child")("optional", "optional")
                ("out-of-range", "out-of-range")("read-only", "read-only")
                ("read-write", "read-write")("required", "required")
                ("root", "root")("target", "target")("valid", "valid")("visited", "visited")
            ;

            // ::
            fixed_filters2.add
                ("after", "after")("before")("before")
                ("first-letter", "first-letter")("first-line", "first-line")
                ("selection", "selection")
            ;

            nth_filters.add
                (":nth-child", ":nth-child")
                (":nth-last-child", ":nth-last-child")(":nth-last-of-type", ":nth-last-of-type")
                (":nth-of-type", ":nth-of-type")
            ;

            ordering_filter =
                   *blank
                >>  qi::char_(qi::_r1)                   [phoenix::push_back(_val, qi::_r1)]
                >>  selector_string                      [_val += qi::_1]
            ;

            filter =
                (
                    (
                            blank
                        >>  selector_string             [_val = qi::_1]
                    )
                    |   ordering_filter('>')            [_val = qi::_1]
                    |   ordering_filter('+')            [_val = qi::_1]
                    |   ordering_filter('~')            [_val = qi::_1]
                    |   (
                               *blank
                            >>  qi::char_(':')          [_a = ":"]
                            >> *blank
                            >>  fixed_filters           [_a += qi::_1]
                        )                               [_val = _a]
                    |   (
                               *blank
                            >>  qi::lit("::")           [_a = "::"]
                            >> *blank
                            >>  fixed_filters2          [_a += qi::_1]
                        )                               [_val = _a]
                    |   (
                                nth_filters
                            >>  qi::char_('(')
                            >>  qi::digit
                            >>  qi::char_(')')
                        )                               [_val = qi::_1]
                    |   (
                                qi::lit(":lang(")       [_a = ":lang("]
                            >>  identifier              [_a += qi::_1]
                            >>  qi::char_(')')          [_a += ")"]
                        )                               [_val = _a]
                    |   (
                                qi::lit(":not(")        [_a = ":not("]
                            >>  selector_string         [_a += qi::_1]
                            >>  qi::char_(')')          [_a += ")"]
                        )                               [_val = _a]
                )
            ;

            selector =
                    *blank
                >>  (
                            attributeSelector               [_val = qi::_1]
                        |   qi::char_('*')                  [at_c <0> (_val) = SelectorType::All]
                        |  +(
                                    qi::char_('.')
                                >>  identifier              [phoenix::push_back(at_c <3> (_val), qi::_1)]
                            )                               [at_c <0> (_val) = SelectorType::Classes]
                        |   (
                                    selector_type           [at_c <0> (_val) = qi::_1]
                                >>  identifier              [at_c <1> (_val) = qi::_1]
                            )
                    )
                >> *filter                              [phoenix::push_back(at_c <2> (_val), qi::_1)]
            ;

            selector_string =
                selector
                [
                    _val = phoenix::bind(&Internal::selectorToString, phoenix::cref(qi::_1))
                ]
            ;

            main %=
                selector % ','
            ;
        }

        // Rules
        qi::rule <Iterator, std::string()> identifier;
        qi::rule <Iterator, std::string()> value;

        qi::rule <Iterator, std::string(char)> ordering_filter;
        qi::rule <Iterator, std::string(), qi::locals <std::string>> filter;

        qi::rule <Iterator, ParsedSelector()> attributeSelector;
        qi::rule <Iterator, SelectorType()> selector_type;
        qi::rule <Iterator, ParsedSelector()> selector;
        qi::rule <Iterator, std::string()> selector_string;

        qi::rule <Iterator, grammar_result()> main;

        // Grammars
        unescaped_string_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD escape_string;

        // Symbols
        qi::symbols<char const, std::string> fixed_filters;
        qi::symbols<char const, std::string> fixed_filters2;
        qi::symbols<char const, std::string> nth_filters;
    };
}
