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
    std::string Point::toString() const
    {
        return left.toString() + " " + top.toString();
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string Point::getTypeString() const
    {
        return "Point";
    }
//---------------------------------------------------------------------------------------------------------------------
    Point* Point::clone() const
    {
        return new Point {*this};
    }
//#####################################################################################################################
} // namespace ValueTypes
} // namespace WretchedCss
