#include "dimensionless.hpp"

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
//#####################################################################################################################
}
}
