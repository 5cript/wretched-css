#include "rule.hpp"

#include <algorithm>

#include "property/value/numerical.hpp"

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
				if (!prop.values.empty() && prop.values[0] && !property.values.empty() && property.values[0])
				{
					auto* numValNew = dynamic_cast <WretchedCss::ValueTypes::NumericValue*> (&*prop.values[0]);
					auto* numValOld = dynamic_cast <WretchedCss::ValueTypes::NumericValue*> (&*property.values[0]);
					if (numValNew &&
						numValOld &&
						numValNew->unit == WretchedCss::ValueTypes::Unit::percent)
					{
						numValNew->value = numValNew->value * numValOld->value / 100.;
						numValNew->unit = numValOld->unit;
					}

					property = prop;
				}
				else
					property = prop;
				return;
            }
        }
        // else, not found
        properties.push_back(prop);
    }
//#####################################################################################################################
} // namespace WretchedCss
