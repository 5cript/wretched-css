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
        static Numerical* create(std::vector <std::string>::const_iterator& begin,
                                 std::vector <std::string>::const_iterator)
        {
            try
            {
                auto* num = new Numerical (boost::lexical_cast <double> (*begin));
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
        static Color* create(std::vector <std::string>::const_iterator& begin,
                             std::vector <std::string>::const_iterator)
        {
            auto maybeColor = tryGetColorFromString(*begin);
            if (!maybeColor)
                return nullptr;

            ++begin;
            return new Color(maybeColor.get());
        }
    };

    template <>
    struct Valueifier <Url>
    {
        static Url* create(std::vector <std::string>::const_iterator& begin,
                           std::vector <std::string>::const_iterator)
        {
            auto maybeUrl = tryGetUrlFromString(*begin);
            if (!maybeUrl)
                return nullptr;

            ++begin;
            return new Url(maybeUrl.get());
        }
    };

    template <>
    struct Valueifier <Size>
    {
        static Size* create(std::vector <std::string>::const_iterator& begin,
                            std::vector <std::string>::const_iterator)
        {
            auto maybeSize = tryGetSizeFromString(*begin);
            if (!maybeSize)
                return nullptr;

            ++begin;
            return new Size(maybeSize.get());
        }
    };

    template <typename... List>
    struct Valueifier <Keyword <List...> >
    {
        static Keyword <List...>* create(std::vector <std::string>::const_iterator& begin,
                                         std::vector <std::string>::const_iterator)
        {
            Keyword <List...> kw(*begin);
            if (kw.verify())
                return new Keyword <List...> (*begin++);
        }
    };

    template <bool reqPos>
    struct Valueifier <Position <reqPos> >
    {
        static Position <reqPos>* create(std::vector <std::string>::const_iterator& begin,
                                         std::vector <std::string>::const_iterator end)
        {
            if (end - begin < (reqPos ? 3 : 2))
                return nullptr;

            auto iter = begin;

            auto left = tryGetSizeFromString(*iter);
            if (!left)
                return nullptr;

            auto top = tryGetSizeFromString(*(++iter));
            if (!top)
                return nullptr;

            if (reqPos)
                if(*(++iter) != "/")
                    return nullptr;

            begin = iter;
            return new Position <reqPos>(left.get(), top.get());
        }
    };

    template <>
    struct Valueifier <Point>
    {
        static Point* create(std::vector <std::string>::const_iterator& begin,
                             std::vector <std::string>::const_iterator end)
        {
            if (end - begin < 2)
                return nullptr;

            auto iter = begin;

            auto left = tryGetSizeFromString(*iter);
            if (!left)
                return nullptr;

            auto top = tryGetSizeFromString(*(++iter));
            if (!top)
                return nullptr;

            begin = iter;
            return new Point(left.get(), top.get());
        }
    };

} // namespace WretchedCss
