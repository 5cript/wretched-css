#pragma once

#include "value/keyword.hpp"
#include "value/numerical.hpp"
#include "value/dimensionless.hpp"
#include "value/string.hpp"
#include "value/url.hpp"
#include "value/point.hpp"
#include "value/color.hpp"

#include <boost/lexical_cast.hpp>

#include <vector>
#include <string>

namespace WretchedCss
{
    using namespace ValueTypes;

    template <typename T>
    struct Valueifier
    {};

    template <>
    struct Valueifier <DimensionlessValue>
    {
        static DimensionlessValue* create(std::vector <RawValue>::const_iterator& begin,
                                          std::vector <RawValue>::const_iterator const&)
        {
            try
            {
                auto* num = new DimensionlessValue (boost::lexical_cast <double> (begin->data));
                ++begin;
                return num;
            }
            catch (boost::bad_lexical_cast const&)
            {
                return nullptr;
            }
        }
    };

    template <>
    struct Valueifier <Color>
    {
        static Color* create(std::vector <RawValue>::const_iterator& begin,
                             std::vector <RawValue>::const_iterator const&)
        {
            auto maybeColor = tryGetColorFromString(begin->data);
            if (!maybeColor)
                return nullptr;

            ++begin;
            return new Color(maybeColor.get());
        }
    };

    template <>
    struct Valueifier <Url>
    {
        static Url* create(std::vector <RawValue>::const_iterator& begin,
                           std::vector <RawValue>::const_iterator const&)
        {
            auto maybeUrl = tryGetUrlFromString(begin->data);
            if (!maybeUrl)
                return nullptr;

            ++begin;
            return new Url(maybeUrl.get());
        }
    };

    template <>
    struct Valueifier <NumericValue>
    {
        static NumericValue* create(std::vector <RawValue>::const_iterator& begin,
                            std::vector <RawValue>::const_iterator const&)
        {
            auto maybeNumericValue = tryGetNumericValueFromString(begin->data);
            if (!maybeNumericValue)
                return nullptr;

            ++begin;
            return new NumericValue(maybeNumericValue.get());
        }
    };

    template <typename... List>
    struct Valueifier <Keyword <List...> >
    {
        static Keyword <List...>* create(std::vector <RawValue>::const_iterator& begin,
                                         std::vector <RawValue>::const_iterator const&)
        {
            Keyword <List...> kw(begin->data);
            if (kw.verify())
            {
                auto* kw = new Keyword <List...> (begin->data);
                ++begin;
                return kw;
            }
            else
                return nullptr;
        }
    };

    template <>
    struct Valueifier <StringValue>
    {
        static StringValue* create(std::vector <RawValue>::const_iterator& begin,
                                   std::vector <RawValue>::const_iterator const& end)
        {
            if (begin != end)
                return new StringValue(begin->data);
            return nullptr;
        }
    };

    template <>
    struct Valueifier <Point>
    {
        static Point* create(std::vector <RawValue>::const_iterator& begin,
                             std::vector <RawValue>::const_iterator const& end)
        {
            auto iter = begin;

            if (iter == end)
                return nullptr;

            auto left = tryGetNumericValueFromString(iter->data);
            if (!left)
                return nullptr;
            else
                ++iter;

            boost::optional <NumericValue> top;
            if (iter != end)
                top = tryGetNumericValueFromString(iter->data);

            if (!top)
            {
                if (left.get().unit == Unit::keyword)
                    top = boost::optional <NumericValue> {NumericValue{Unit::keyword, 0., "center"}};
                else
                    top = boost::optional <NumericValue> {NumericValue{Unit::percent, 50., ""}};
            }
            else
                ++iter;

            if (left.get().unit == Unit::keyword)
                if (left.get().strValue == "bottom" || left.get().strValue == "top")
                    std::swap(left, top);

            begin = iter;
            return new Point (left.get(), top.get());
        }
    };


} // namespace WretchedCss
