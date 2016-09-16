#include "numerical.hpp"

#include "twisted-spirit/core/parse.hpp"

namespace WretchedCss
{
//#####################################################################################################################
    boost::optional <ValueTypes::NumericValue> tryGetNumericValueFromString(std::string const& str)
    {
        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(size_grammar);
        auto maybeNumericValue = parse<grammar>(str);

        if (maybeNumericValue.first == ParsingResult::FULL_SUCCESS)
        {
            auto result = maybeNumericValue.second;
            return boost::optional <ValueTypes::NumericValue> {result};
        }
        return boost::none;
    }
//#####################################################################################################################
}
