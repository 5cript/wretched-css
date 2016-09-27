#include "url.hpp"

#ifndef __BORLANDC__
#	include "twisted-spirit/core/parse.hpp"
#	include "../../../../parser/url.hpp"
#endif

namespace WretchedCss { namespace ValueTypes
{
//####################################################################################
    Url::Url(std::string value)
        : value(std::move(value))
    {

    }
//------------------------------------------------------------------------------------
    std::string Url::getTypeString() const
    {
        return "Url";
    }
//------------------------------------------------------------------------------------
    std::string Url::toString() const
    {
        return "url(\"" + value + "\")";
    }
//------------------------------------------------------------------------------------
    Url* Url::clone() const
    {
        return new Url{*this};
    }
//####################################################################################
    boost::optional <Url> tryGetUrlFromString(std::string const& str)
	{
#ifndef __BORLANDC__
		using namespace TwistedSpirit;

		TYPEDEF_GRAMMAR(url_grammar);
		auto maybeUrl = parse<grammar>(str);

		if (maybeUrl.first == ParsingResult::FULL_SUCCESS)
			return boost::optional <Url> (maybeUrl.second);
#endif
        return boost::none;
    }
//####################################################################################
} // namespace ValueTypes
} // namespace WretchedCss
