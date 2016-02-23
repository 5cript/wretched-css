#pragma once

#include "../rule_set/rule/property/known_properties.hpp"
#include "../rule_set/rule/property/property.hpp"

namespace WretchedCss
{

    Property parseProperty(std::string const& property);

} // namespace WretchedCss
