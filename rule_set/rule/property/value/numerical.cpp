#include "numerical.hpp"

#ifndef __BORLANDC__
#	include "twisted-spirit/core/parse.hpp"
#	include "../../../../parser/numerical.hpp"
#endif

#include <map>
#include <stdexcept>
#include <cstdint>

#include <sstream>
#include <iomanip>

namespace WretchedCss { namespace ValueTypes
{
//####################################################################################
    NumericValue::NumericValue(Unit unit, double value)
        : unit(unit)
        , value(value)
    {

    }
//-----------------------------------------------------------------------------------
    std::string NumericValue::getTypeString() const
    {
        return "NumericValue";
    }
//-----------------------------------------------------------------------------------
    std::string NumericValue::toString() const
    {
        std::stringstream sstr;
        sstr << std::setprecision(3) << value << unitToString(unit);
        return sstr.str();
    }
//-----------------------------------------------------------------------------------
    NumericValue* NumericValue::clone() const
    {
        return new NumericValue {*this};
    }
//####################################################################################
    Unit getUnitFromString(std::string const& unit)
    {
        static const std::map <std::string, Unit> map =
        {
            {"em", Unit::em},
            {"ex", Unit::ex},
            {"percent", Unit::percent},
            {"%", Unit::percent},
            {"px", Unit::px},
            {"cm", Unit::cm},
            {"mm", Unit::mm},
            {"in", Unit::in},
            {"pt", Unit::pt},
            {"pc", Unit::pc},
            {"ch", Unit::ch},
            {"rem", Unit::rem},
            {"vh", Unit::vh},
            {"vw", Unit::vw},
            {"vmin", Unit::vmin},
            {"vmax", Unit::vmax}
        };

        auto i = map.find(unit);

        if (i != std::end(map))
            return i->second;

        throw std::invalid_argument("this is not a valid unit");
    }
//-----------------------------------------------------------------------------------
    std::string unitToString(Unit unit)
	{
		/*
		static const std::map <uint32_t, std::string> map =
		{
			{static_cast <uint32_t> (Unit::em), "em"},
			{static_cast <uint32_t> (Unit::ex), "ex"},
			{static_cast <uint32_t> (Unit::percent), "%"},
			{static_cast <uint32_t> (Unit::px), "px"},
			{static_cast <uint32_t> (Unit::cm), "cm"},
			{static_cast <uint32_t> (Unit::mm), "mm"},
			{static_cast <uint32_t> (Unit::in), "in"},
			{static_cast <uint32_t> (Unit::pt), "pt"},
			{static_cast <uint32_t> (Unit::pc), "pc"},
			{static_cast <uint32_t> (Unit::ch), "ch"},
			{static_cast <uint32_t> (Unit::rem), "rem"},
			{static_cast <uint32_t> (Unit::vh), "vh"},
			{static_cast <uint32_t> (Unit::vw), "vw"},
			{static_cast <uint32_t> (Unit::vmin), "vmin"},
			{static_cast <uint32_t> (Unit::vmax), "vmax"}
		};

		auto i = map.find(static_cast <uint32_t> (unit));

		if (i != std::end(map))
			return i->second;

		throw std::invalid_argument("this is not a valid unit");

        //return std::string{map.at(static_cast <uint32_t> (unit))};
		*/

		switch (unit)
		{
			case(Unit::em): return "em";
			case(Unit::ex): return "ex";
			case(Unit::percent): return "%";
			case(Unit::px): return "px";
			case(Unit::cm): return "cm";
			case(Unit::mm): return "mm";
			case(Unit::in): return "in";
			case(Unit::pt): return "pt";
			case(Unit::pc): return "pc";
			case(Unit::ch): return "ch";
			case(Unit::rem): return "rem";
			case(Unit::vh): return "vh";
			case(Unit::vw): return "vw";
			case(Unit::vmin): return "vmin";
			case(Unit::vmax): return "vmax";
			default:
				throw std::invalid_argument("this is not a valid unit");
		}

    }
//-----------------------------------------------------------------------------------
    boost::optional <NumericValue> tryGetNumericValueFromString(std::string const& str)
	{
#ifndef __BORLANDC__
		using namespace TwistedSpirit;

		TYPEDEF_GRAMMAR(size_grammar);
		auto maybeNumericValue = parse<grammar>(str);

		if (maybeNumericValue.first == ParsingResult::FULL_SUCCESS)
		{
			auto result = maybeNumericValue.second;
			return boost::optional <NumericValue> {result};
		}
#endif
        return boost::none;
    }
//####################################################################################

} // namespace ValueTypes
} // namespace WretchedCss

