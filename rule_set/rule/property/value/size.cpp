#include "size.hpp"

#include "twisted-spirit/core/parse.hpp"
#include "../../../../parser/size.hpp"

#include <map>
#include <stdexcept>
#include <cstdint>

namespace WretchedCss { namespace ValueTypes
{
//####################################################################################
    SizeUnit getUnitFromString(std::string const& unit)
    {
        static const std::map <std::string, SizeUnit> map =
        {
            {"em", SizeUnit::em},
            {"ex", SizeUnit::ex},
            {"percent", SizeUnit::percent},
            {"px", SizeUnit::px},
            {"cm", SizeUnit::cm},
            {"mm", SizeUnit::mm},
            {"in", SizeUnit::in},
            {"pt", SizeUnit::pt},
            {"pc", SizeUnit::pc},
            {"ch", SizeUnit::ch},
            {"rem", SizeUnit::rem},
            {"vh", SizeUnit::vh},
            {"vw", SizeUnit::vw},
            {"vmin", SizeUnit::vmin},
            {"vmax", SizeUnit::vmax}
        };

        auto i = map.find(unit);

        if (i != std::end(map))
            return i->second;

        throw std::invalid_argument("this is not a valid unit");
    }
//-----------------------------------------------------------------------------------
    std::string unitToString(SizeUnit unit)
    {
        static const std::map <uint32_t, std::string> map =
        {
            {static_cast <uint32_t> (SizeUnit::em), "em"},
            {static_cast <uint32_t> (SizeUnit::ex), "ex"},
            {static_cast <uint32_t> (SizeUnit::percent), "percent"},
            {static_cast <uint32_t> (SizeUnit::px), "px"},
            {static_cast <uint32_t> (SizeUnit::cm), "cm"},
            {static_cast <uint32_t> (SizeUnit::mm), "mm"},
            {static_cast <uint32_t> (SizeUnit::in), "in"},
            {static_cast <uint32_t> (SizeUnit::pt), "pt"},
            {static_cast <uint32_t> (SizeUnit::pc), "pc"},
            {static_cast <uint32_t> (SizeUnit::ch), "ch"},
            {static_cast <uint32_t> (SizeUnit::rem), "rem"},
            {static_cast <uint32_t> (SizeUnit::vh), "vh"},
            {static_cast <uint32_t> (SizeUnit::vw), "vw"},
            {static_cast <uint32_t> (SizeUnit::vmin), "vmin"},
            {static_cast <uint32_t> (SizeUnit::vmax), "vmax"}
        };

        return map.at(static_cast <uint32_t> (unit));
    }
//-----------------------------------------------------------------------------------
    boost::optional <Size> tryGetSizeFromString(std::string const& str)
    {
        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(size_grammar);
        auto maybeSize = parse<grammar>(str);

        if (maybeSize.first == ParsingResult::FULL_SUCCESS)
        {
            auto result = maybeSize.second;
            return boost::optional <Size> {result};
        }
        return boost::none;
    }
//####################################################################################

} // namespace ValueTypes
} // namespace WretchedCss

