#pragma once

#include "value/keyword.hpp"
#include "value/numerical.hpp"
#include "value/size.hpp"
#include "value/string.hpp"
#include "value/url.hpp"
#include "value/point.hpp"
#include "value/color.hpp"
#include "value/position.hpp"

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
    struct Valueifier <Numerical>
    {
        static Numerical* create(std::vector <RawValue>::const_iterator& begin,
                                 std::vector <RawValue>::const_iterator const&)
        {
            try
            {
                auto* num = new Numerical (boost::lexical_cast <double> (begin->data));
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
    struct Valueifier <Size>
    {
        static Size* create(std::vector <RawValue>::const_iterator& begin,
                            std::vector <RawValue>::const_iterator const&)
        {
            auto maybeSize = tryGetSizeFromString(begin->data);
            if (!maybeSize)
                return nullptr;

            ++begin;
            return new Size(maybeSize.get());
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
        }
    };

    template <bool reqPos>
    struct Valueifier <Position <reqPos> >
    {
        static Position <reqPos>* create(std::vector <RawValue>::const_iterator& begin,
                                         std::vector <RawValue>::const_iterator const& end)
        {
            if (end - begin < (reqPos ? 3 : 2))
                return nullptr;

            auto iter = begin;

            auto left = tryGetSizeFromString(iter->data);
            if (!left)
                return nullptr;

            auto top = tryGetSizeFromString((++iter)->data);
            if (!top)
                return nullptr;

            if (reqPos)
                if((++iter)->data != "/")
                    return nullptr;

            begin = iter;
            return new Position <reqPos>(left.get(), top.get());
        }
    };

    template <>
    struct Valueifier <Point>
    {
        static Point* create(std::vector <RawValue>::const_iterator& begin,
                             std::vector <RawValue>::const_iterator const& end)
        {
            if (end - begin < 2)
                return nullptr;

            auto iter = begin;

            auto left = tryGetSizeFromString(iter->data);
            if (!left)
                return nullptr;

            auto top = tryGetSizeFromString((++iter)->data);
            if (!top)
                return nullptr;

            begin = iter;
            return new Point(left.get(), top.get());
        }
    };

} // namespace WretchedCss
