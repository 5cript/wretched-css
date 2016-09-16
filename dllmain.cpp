#include "dllmain.h"

#include "rule_set/rule_set.hpp"

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
extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    return TRUE; // succesful
}
//---------------------------------------------------------------------------------------------------------------------
C_LINKAGE DLL_EXPORT void json_to_css(const char* json, char** css)
{
    WretchedCss::RuleSet rules;
    rules.fromJson(json);
    auto cssString = rules.toCss();
    *css = allocateCString(cssString);
}
//---------------------------------------------------------------------------------------------------------------------
C_LINKAGE DLL_EXPORT void css_to_json(const char* css, char** json)
{
    WretchedCss::RuleSet rules{{css}};
    auto jsonString = rules.toJson();
    *json = allocateCString(jsonString);
}
//---------------------------------------------------------------------------------------------------------------------
C_LINKAGE DLL_EXPORT void free_buffer(char* buffer)
{
    delete buffer;
}
//---------------------------------------------------------------------------------------------------------------------
