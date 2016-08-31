#include "dllmain.h"

#include <cstring>
#include <string>

//#####################################################################################################################
char* allocateCString(std::string const& str)
{
    char* cstr = new char[str.length() + 1];
    std::memcpy(cstr, str.c_str(), str.length());
    cstr[str.length()] = '\0';
    return cstr;
}
//---------------------------------------------------------------------------------------------------------------------
extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE /* hinstDLL */, DWORD /* fdwReason */, LPVOID /* lpvReserved */)
{
    return TRUE; // succesful
}
//---------------------------------------------------------------------------------------------------------------------
C_LINKAGE DLL_EXPORT void free_buffer(char* buffer)
{
    delete buffer;
}
//#####################################################################################################################
