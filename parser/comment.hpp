#pragma once

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/core/confix.hpp"

namespace WretchedCss
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct css_comment_remover : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        css_comment_remover() : css_comment_remover::base_type(main, "rule_set")
        {
            using namespace common_usings;

            comment =
                confix("/*", "*/")
                [
                    *(qi::char_ - "*/")
                ]
            ;

            no_comment =
                +(qi::char_ - "/*")
            ;

            main =
                   *comment
                >> *(
                            no_comment              [_val += qi::_1]
                        >> *comment
                    )
            ;
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;
        qi::rule <Iterator, std::string()> no_comment;
        qi::rule <Iterator> comment;
    };
}
