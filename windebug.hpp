#ifndef WINDEBUG_HPP_INCLUDED
#define WINDEBUG_HPP_INCLUDED

#include <exception>
#include <string>

namespace WretchedCss
{
    void DisplayMessage(std::string const& str);
    void DisplayError(std::exception const& exc);
}

#endif // WINDEBUG_HPP_INCLUDED
