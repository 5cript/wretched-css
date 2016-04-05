#include "dimensionless.hpp"

#include <sstream>
#include <iomanip>

namespace WretchedCss { namespace ValueTypes
{
//#####################################################################################################################
    std::string DimensionlessValue::getTypeString() const
    {
        return "DimensionlessValue";
    }
//---------------------------------------------------------------------------------------------------------------------
    DimensionlessValue::DimensionlessValue(double value)
        : value(value)
    {

    }
//---------------------------------------------------------------------------------------------------------------------
    std::string DimensionlessValue::toString() const
    {
        std::stringstream sstr;
        sstr << std::setprecision(3) << value;
        return sstr.str();
    }
//#####################################################################################################################
}
}
