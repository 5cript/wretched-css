#include "point.hpp"

namespace WretchedCss { namespace ValueTypes
{
//#####################################################################################################################
    Point::Point(NumericValue left, NumericValue top)
        : left(std::move(left))
        , top(std::move(top))
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    std::string Point::getTypeString() const
    {
        return "Point";
    }
//#####################################################################################################################
} // namespace ValueTypes
} // namespace WretchedCss
