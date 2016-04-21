#include "property.hpp"

namespace WretchedCss
{
//#####################################################################################################################
    Property::Property(std::string key, std::vector <std::unique_ptr <Value>> const& values)
        : key(std::move(key))
        , values()
    {
        for (auto const& i : values)
            this->values.emplace_back(i->clone());
    }
//---------------------------------------------------------------------------------------------------------------------
    Property& Property::operator=(Property const& property)
    {
        key = property.key;
        values.clear();
        for (auto const& i : property.values)
            values.emplace_back(i->clone());
        return *this;
    }
//---------------------------------------------------------------------------------------------------------------------
    Property::Property(Property const& property)
        : Property(property.key, property.values)
    {
    }
//#####################################################################################################################
}
