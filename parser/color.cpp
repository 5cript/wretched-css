#include "color.hpp"

namespace WretchedCss { namespace Internal
{
//####################################################################################
    ValueTypes::Color toRgb(ValueTypes::HslColor const& hsl)
    {
        auto const hueToRgb = [](double v1, double v2, double vH)
        {
            if (vH < 0.)
                vH += 1;
            if (vH > 1.)
                vH -= 1;

            if ((6 * vH) < 1.)
                return (v1 + (v2 - v1) * 6 * vH);
            if ((2 * vH) < 1.)
                return v2;
            if ((3 * vH) < 2.)
                return (v1 + (v2 - v1) * ((2. / 3) - vH) * 6);

            return v1;
        };

        ValueTypes::Color rgb;
        rgb.a = hsl.a;
        if (hsl.s == 0)
        {
            rgb.r = rgb.g = rgb.b = static_cast <uint8_t>(hsl.l * 255);
        }
        else
        {
            double v1, v2;
            double hue = (double)hsl.h / 360.;

            v2 = (hsl.l < 0.5) ? (hsl.l * (1 + hsl.s)) : ((hsl.l + hsl.s) - (hsl.l * hsl.s));
            v1 = 2 * hsl.l - v2;

            rgb.r = static_cast <uint8_t>(std::min(255., 255. * hueToRgb(v1, v2, hue + (1.0f / 3)) + 0.5));
            rgb.g = static_cast <uint8_t>(std::min(255., 255. * hueToRgb(v1, v2, hue) + 0.5));
            rgb.b = static_cast <uint8_t>(std::min(255., 255. * hueToRgb(v1, v2, hue - (1.0f / 3)) + 0.5));
        }

        return rgb;
    }
//-----------------------------------------------------------------------------------
    ValueTypes::Color toRgbFromHex(uint32_t hex)
    {
        ValueTypes::Color color;
        color.r = (hex & 0x00FF0000) >> 16;
        color.g = (hex & 0x0000FF00) >> 8;
        color.b = (hex & 0x000000FF);
        color.a = 0;

        return color;
    }
//####################################################################################
} // namespace Internal
} // namespace WretchedCss
