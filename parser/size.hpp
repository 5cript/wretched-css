#pragma once

#include "../rule_set/rule/property/value/size.hpp"

#include "twisted-spirit/core/parser_core.hpp"

namespace WretchedCss
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct size_grammar : qi::grammar <Iterator, ValueTypes::Size()>
    {
        using grammar_result = ValueTypes::Size;

        size_grammar() : size_grammar::base_type(main, "size")
        {
            using namespace common_usings;
            using namespace ValueTypes;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			unit.add
                ("em", SizeUnit::em)
                ("ex", SizeUnit::ex)
                ("%", SizeUnit::percent)
                ("px", SizeUnit::px)
                ("cm", SizeUnit::cm)
                ("mm", SizeUnit::mm)
                ("in", SizeUnit::in)
                ("pt", SizeUnit::pt)
                ("pc", SizeUnit::pc)
                ("ch", SizeUnit::ch)
                ("rem", SizeUnit::rem)
                ("vh", SizeUnit::vh)
                ("vw", SizeUnit::vw)
                ("vmin", SizeUnit::vmin)
                ("vmax", SizeUnit::vmax)
			;

            main =
                    double_                     [at_c <1> (_val) = qi::_1]
                >>  qi::no_case
                    [
                        unit                    [at_c <0> (_val) = qi::_1]
                    ]
            ;
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;

        // Symbols
        qi::symbols <char const, ValueTypes::SizeUnit> unit;
    };

} // namespace WretchedCss
