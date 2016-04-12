#include "color.hpp"

#include "twisted-spirit/core/parse.hpp"

#include "../../../../parser/color.hpp"

#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace WretchedCss { namespace ValueTypes
{
//####################################################################################
    Color::Color (uint8_t r, uint8_t g, uint8_t b, double a)
        : r(r)
        , g(g)
        , b(b)
        , a(a)
    {

    }
//-----------------------------------------------------------------------------------
    std::string Color::getTypeString() const
    {
        return "Color";
    }
//-----------------------------------------------------------------------------------
    std::string Color::toString() const
    {
        std::stringstream result;
        if (a > 0.000001)
        {
            result << "rgba(";
            result << (int)r << ", " << (int)g << ", " << (int)b << ", " << std::setprecision(3) << (double)a;
            result << ")";
        }
        else
        {
            result << "#" << std::hex <<
                std::setw(2) << std::setfill('0') << (int)r <<
                std::setw(2) << std::setfill('0') << (int)g <<
                std::setw(2) << std::setfill('0') << (int)b;
        }
        return result.str();
    }
//-----------------------------------------------------------------------------------
    Color* Color::clone() const
    {
        return new Color{*this};
    }
//####################################################################################
    Color ColorFromString(std::string const& color)
    {
        auto maybeColor = tryGetColorFromString(color);
        if (!maybeColor)
            throw std::invalid_argument("Argument is not a valid css color string");

        return maybeColor.get();
    }
//-----------------------------------------------------------------------------------
    boost::optional <Color> tryGetColorFromString(std::string const& color)
    {
        using namespace TwistedSpirit;

        TYPEDEF_GRAMMAR(color_grammar);
        auto maybeColor = parse<grammar>(color);

        if (maybeColor.first == ParsingResult::FULL_SUCCESS)
        {
            auto result = maybeColor.second;
            result.originalString = color;
            return boost::optional <Color> {result};
        }
        return boost::none;
    }
//####################################################################################

} // namespace ValueTypes
} // namespace WretchedCss
