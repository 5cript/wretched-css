#pragma once

#include "../rule_set/rule/selector.hpp"

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/rules/space.hpp"

#include <vector>
#include <string>

namespace WretchedCss
{
    struct IntermediateRule
    {
        std::string selector;
        std::vector <std::string> declarations;
    };

    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct rule_set_grammar : qi::grammar <Iterator, std::vector <IntermediateRule>()>
    {
        using grammar_result = std::vector <IntermediateRule>;

        rule_set_grammar() : rule_set_grammar::base_type(main, "rule_set")
        {
            using namespace common_usings;
            INSTALL_ERROR_HANDLER;
            INSTALL_WARNING_HANDLER;
            INSTALL_DEBUG_HANDLER;

            declaration.name("css_property_declaration");

            selector %=
                *(qi::char_ - qi::char_('{'))
            ;

            declaration %=
                    +(qi::char_ - qi::char_(";{}"))
                >   ';'
            ;

            declarations =
               *(
                       *blank
                    >>  declaration                 [phoenix::push_back(_val, qi::_1)]
                    >> *blank
                )
            ;

            rule =
                   *blank
                >>  selector                        [at_c <0> (_val) = qi::_1]
                >> *blank
                >>  qi::char_('{')
                >> *blank
                >>  declarations                    [at_c <1> (_val) = qi::_1]
                >> *blank
                >>  qi::char_('}')
                >> *blank
            ;

            main %=
               +rule
            ;

            HANDLE_QI_ERROR(main, 1);
            HANDLE_QI_WARNING(main, 1);
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;
        qi::rule <Iterator, IntermediateRule()> rule;
        qi::rule <Iterator, std::string()> selector;
        qi::rule <Iterator, std::string()> declaration;
        qi::rule <Iterator, std::vector <std::string>()> declarations;
    };
} // namespace WretchedCss

BOOST_FUSION_ADAPT_STRUCT
(
    WretchedCss::IntermediateRule,
    selector, declarations
)
