#include "selector.hpp"

#include "twisted-spirit/core/parse.hpp"

#include "../../parser/selector.hpp"

#include <cmath>
#include <algorithm>

namespace WretchedCss
{
//#####################################################################################################################
    std::string ParsedSelector::toString() const
    {
        std::string result;

        if (type == SelectorType::Classes)
        {
            for (auto const& i : classes)
            {
                result.push_back('.');
                result += i;
            }
        }
        else
        {
            switch(type)
            {;
            case(SelectorType::Id):
                result.push_back('#');
                break;
            case(SelectorType::All):
                result.push_back('*');
                break;
            case(SelectorType::Attribute):
                result.push_back('[');
                break;
            //case (SelectorType::Type):
            //    result.push_back(' ');
            //    break;
            default:
                break;
            }
            result += selectorString;
        }

        if (type == SelectorType::Attribute)
            result.push_back(']');

        for (auto const& filter : filters)
        {
            result.push_back(' ');
            result += filter;
        }

        return result;
    }
//---------------------------------------------------------------------------------------------------------------------
    long ParsedSelector::calculateSpecificity() const
    {
        long res = 0;

        if (type == SelectorType::Id)
        {
            res += 100;
        }
        else if (type == SelectorType::Classes)
            res += 10 * classes.size();
        else if (type == SelectorType::Element)
            res += 1;
        else if (type == SelectorType::Attribute)
            res += 1;

        for (auto const& filter : filters)
        {
            if (filter.empty())
                continue;

            res += 1;
        }

        return res;
    }
//---------------------------------------------------------------------------------------------------------------------
    bool ParsedSelector::canSelect(std::string const& selector) const
    {
        if (selector.empty())
            return false;
        if (type == SelectorType::All && filters.empty())
            return true;

        TYPEDEF_GRAMMAR(selector_grammar);
        auto result = parse<grammar>(selector);

        using namespace std::string_literals;

        if (result.first != ParsingResult::FULL_SUCCESS)
            throw std::invalid_argument("selector is not a valid selector: "s + selector);

        #define DOES_NOT_APPLY \
        { \
            applies = false; \
            continue; \
        }

        bool applies = true;
        for (auto const currentSelector : result.second)
        {
            applies = true;

            if (currentSelector.type != type)
                DOES_NOT_APPLY

            if (type != SelectorType::Classes && currentSelector.selectorString != selectorString)
                DOES_NOT_APPLY

            if (type == SelectorType::Classes && currentSelector.type == SelectorType::Classes)
            {
                bool found = false;
                for (auto const& clas : currentSelector.classes)
                {
                    if (std::find(std::begin(classes), std::end(classes), clas) != std::end(classes))
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                    DOES_NOT_APPLY
            }

            if (filters != currentSelector.filters)
                DOES_NOT_APPLY
        }

        return applies;
    }
//#####################################################################################################################
    Selector::Selector(std::string const& raw)
    {
        TYPEDEF_GRAMMAR(selector_grammar);
        auto result = parse<grammar>(raw);

        using namespace std::string_literals;

        if (result.first != ParsingResult::FULL_SUCCESS)
            throw std::invalid_argument("selector is not a valid selector: "s + raw);

        selectors_ = result.second;

        /*
        for (auto const& i : selectors_)
        {
            std::cout << "type: " << (int)i.type << "\n";
            std::cout << "selectorString: " << i.selectorString << "\n";
            for (auto const& filter : i.filters)
            {
                std::cout << "filter: " << filter << "\n";
            }
            std::cout << "\n";
        }
        */
    }
//---------------------------------------------------------------------------------------------------------------------
    std::string Selector::toString() const
    {
        if (selectors_.empty())
            return "";

        std::string result;
        for (auto i = std::begin(selectors_), end = std::end(selectors_);
             i < end - 1; ++i)
        {
            result += i->toString();
            result += ", ";
        }
        result += selectors_.back().toString();
        return result;
    }
//---------------------------------------------------------------------------------------------------------------------
    std::vector <ParsedSelector> Selector::getSelectors() const
    {
        return selectors_;
    }
//---------------------------------------------------------------------------------------------------------------------
    long Selector::getHighestSpecificityFor(std::string const& selector)
    {
        long max = -1;
        for (auto const& i : selectors_)
        {
            if (i.canSelect(selector))
                max = std::max(max, i.calculateSpecificity());
        }
        return max;
    }
//#####################################################################################################################
}
