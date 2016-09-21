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
//---------------------------------------------------------------------------------------------------------------------
	Property* Rule::operator[](std::string const& key)
	{
		for (auto& property : properties)
		{
			if (property.key == key)
			{
				return &property;
			}
		}
		return nullptr;
	}
//---------------------------------------------------------------------------------------------------------------------
	void Rule::addProperty(Property const& prop)
	{
		for (auto& property : properties)
        {
            // overwrite if found
			if (property.key == prop.key)
            {
                property = prop;
                return;
            }
        }
        // else, not found
        properties.push_back(prop);
    }
//#####################################################################################################################
} // namespace WretchedCss
