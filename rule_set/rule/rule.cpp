#include "rule.hpp"

#include <algorithm>

namespace WretchedCss
{
//#####################################################################################################################
    boost::optional <Property> Rule::operator[](std::string const& propertyName) const
    {
        for (auto const& prop : properties)
        {
            if (prop.key == propertyName && !prop.values.empty())
                return boost::optional <Property> {prop};
        }
        return boost::none;
    }
//#####################################################################################################################
} // namespace WretchedCss
