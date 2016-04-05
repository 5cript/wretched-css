#pragma once

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/rules/space.hpp"

#include "../rule_set/rule/property/value/url.hpp"

namespace WretchedCss
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct url_grammar : qi::grammar <Iterator, std::string()>
    {
        using grammar_result = std::string;

        url_grammar() : url_grammar::base_type(main, "url")
        {
            using namespace common_usings;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;

			no_close_paren = qi::char_ - qi::char_(')');

			no_quote = qi::char_ - qi::char_('"');

			main =
                    qi::lit("url(")
                >> *space
                >>  ((
                            qi::char_('"')
                        >> *no_quote            [phoenix::push_back(_val, qi::_1)]
                        >>  qi::char_('"')
                    )
                    |
                    (
                            no_close_paren      [phoenix::push_back(_val, qi::_1)]
                    ))
                >> *space
                >>  qi::char_(')')
			;
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;
        qi::rule <Iterator, char()> no_close_paren;
        qi::rule <Iterator, char()> no_quote;
    };

} // namespace WretchedCss
