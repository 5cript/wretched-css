#pragma once

#include "../rule_set/rule/property/value/numerical.hpp"

#include "twisted-spirit/core/parser_core.hpp"

namespace WretchedCss
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct size_grammar : qi::grammar <Iterator, ValueTypes::NumericValue()>
    {
        using grammar_result = ValueTypes::NumericValue;

        size_grammar() : size_grammar::base_type(main, "size")
        {
            using namespace common_usings;
            using namespace ValueTypes;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			unit.add
                ("em", Unit::em)
                ("ex", Unit::ex)
                ("%", Unit::percent)
                ("px", Unit::px)
                ("cm", Unit::cm)
                ("mm", Unit::mm)
                ("in", Unit::in)
                ("pt", Unit::pt)
                ("pc", Unit::pc)
                ("ch", Unit::ch)
                ("rem", Unit::rem)
                ("vh", Unit::vh)
                ("vw", Unit::vw)
                ("vmin", Unit::vmin)
                ("vmax", Unit::vmax)
			;

			posKeyword.add
                ("left", "left")
                ("right", "right")
                ("center", "center")
                ("top", "top")
                ("bottom", "bottom")
			;

            main =
                (
                        double_                     [at_c <1> (_val) = qi::_1]
                    >>  qi::no_case
                        [
                            unit                    [at_c <0> (_val) = qi::_1]
                        ]
                )
                |
                (
                        posKeyword                  [at_c <2> (_val) = qi::_1]
                    >>  eps                         [at_c <0> (_val) = Unit::keyword]
                )
            ;
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;

        // Symbols
        qi::symbols <char const, ValueTypes::Unit> unit;
        qi::symbols <char const, std::string> posKeyword;
    };

} // namespace WretchedCss
