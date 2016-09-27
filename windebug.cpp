#include "windebug.hpp"

#include <windows.h>

namespace WretchedCss
{
//#####################################################################################################################
    void DisplayMessage(std::string const& str)
    {
        MessageBox(
            NULL,
            str.c_str(),
            "Wretched CSS Library",
            MB_OK
        );
    }
//---------------------------------------------------------------------------------------------------------------------
    void DisplayError(std::exception const& exc)
    {
        DisplayMessage(exc.what());
    }
//#####################################################################################################################
}
