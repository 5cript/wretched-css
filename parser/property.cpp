#include "property.hpp"
//#include "../rule_set/rule/property/known_properties.hpp"
#include "../rule_set/rule/property/valueifier.hpp"

#include "twisted-spirit/core/parser_core.hpp"
#include "twisted-spirit/core/parse.hpp"
#include "twisted-spirit/grammars/unescaped_string.hpp"

#include "mplex/type_print/type_print.hpp"

#include <stdexcept>
#include <iostream>

namespace WretchedCss
{
    using namespace TwistedSpirit;

    template GRAMMAR_TEMPLATE_SIGNATURE
    struct raw_property_grammar : qi::grammar <Iterator, RawProperty()>
    {
        using grammar_result = RawProperty;

        raw_property_grammar() : raw_property_grammar::base_type(main, "raw_property")
        {
            using namespace common_usings;
            using namespace ValueTypes;
            INSTALL_ERROR_HANDLER;
			INSTALL_WARNING_HANDLER;
			INSTALL_DEBUG_HANDLER;

			key %=
                    +(qi::char_ - qi::char_(':'))
                >>  ':'
			;

			atomic =
                (
                    (
                        qi::char_('/')                                      [_val = "/"]
                    )
                    |
                    (
                            qi::lit("url(")                                 [_val = "url(\""]
                        >>  unescaped                                       [_val += qi::_1]
                        >>  qi::char_(')')                                  [phoenix::push_back(_val, '"'), phoenix::push_back(_val, qi::_1)]
                    )
                    |
                    (
                        // solid segment.
                        +(qi::char_ - (qi::space | qi::char_(",/")))        [phoenix::push_back(_val, qi::_1)]
                    )
                )
			;

			values =
               +(
                    (
                        atomic
                        [
                            at_c <0> (_a) = qi::_1,
                            at_c <1> (_a) = false,
                            phoenix::push_back(_val, _a)
                        ]
                        |
                        (
                            (
                                   *qi::space
                                >>  atomic                                          [at_c <0> (_a) = qi::_1, at_c <1> (_a) = true]
                                >> *qi::space
                                >>  eps                                             [phoenix::push_back(_val, _a)]
                            ) % ','
                        )
                    ) % (+qi::space)
                )
            ;


            main =
                    key                         [at_c <0> (_val) = qi::_1]
                >>  values                      [at_c <1> (_val) = qi::_1]
            ;
        }

        // Rules
        qi::rule <Iterator, grammar_result()> main;
        qi::rule <Iterator, std::string()> key;
        qi::rule <Iterator, std::vector <RawValue>(), qi::locals <RawValue> > values;
        qi::rule <Iterator, std::string()> atomic;
        qi::rule <Iterator, std::string()> value;

        // Grammars
        unescaped_string_grammar GRAMMAR_TEMPLATE_SIGNATURE_FORWARD unescaped;
    };

//#####################################################################################################################
    RawProperty preprocessProperty(std::string const& property)
    {
        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(raw_property_grammar);
        auto maybeRawProperty = parse<grammar>(property);

        if (maybeRawProperty.first == ParsingResult::FAIL)
            throw std::invalid_argument("argument is not a well formed property");

        return maybeRawProperty.second;
    }
//#####################################################################################################################
    Property parseProperty(std::string const& property)
    {
        Property p;

        // first generate a raw property
        auto raw = preprocessProperty(property);

        p.key = raw.key;

        #define VALUEIFY_TYPE(Type) \
            value = Valueifier <Type>::create(i, end); \
            if (value != nullptr) \
            { \
                p.values.emplace_back(value); \
                continue; \
            }

        for (auto i = std::cbegin(raw.values), end = std::cend(raw.values); i < end; )
        {
            Value* value;

            VALUEIFY_TYPE(Url);
            VALUEIFY_TYPE(Color);
            VALUEIFY_TYPE(NumericValue);
            VALUEIFY_TYPE(DimensionlessValue);
            VALUEIFY_TYPE(StringValue);
        }

        #undef VALUEIFY_TYPE

        return p;
    }
//#####################################################################################################################
} // namespace WretchedCss
