#include "dllmain.h"

#include "rule_set/rule_set.hpp"

#ifndef Q_MOC_RUN // A Qt workaround, for those of you who use Qt
#   include "SimpleJSON/parse/jsd.hpp"
#   include "SimpleJSON/parse/jsd_convenience.hpp"
#   include "SimpleJSON/stringify/jss.hpp"
#   include "SimpleJSON/stringify/jss_fusion_adapted_struct.hpp"
#endif

#include "rule_set/rule/selector.hpp"

#include "windebug.hpp"

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
    try
    {
        WretchedCss::RuleSet rules;
        rules.fromJson(json);
        auto cssString = rules.toCss();
        *css = allocateCString(cssString);
    }
    catch (std::exception const& exc)
    {
        WretchedCss::DisplayError(exc);
    }
}
//---------------------------------------------------------------------------------------------------------------------
C_LINKAGE DLL_EXPORT void css_to_json(const char* css, char** json)
{
    try
    {
        WretchedCss::RuleSet rules{{css}};
        auto jsonString = rules.toJson();
        *json = allocateCString(jsonString);
    }
    catch (std::exception const& exc)
    {
        WretchedCss::DisplayError(exc);
    }
}
//---------------------------------------------------------------------------------------------------------------------
C_LINKAGE DLL_EXPORT result_type selector_to_json(const char* selector, char** json)
{
    try
    {
        WretchedCss::Selector stor(selector);
        std::stringstream sstr;
        sstr << '{';
        JSON::stringify(sstr, "selector", stor, JSON::ProduceNamedOutput);
        sstr << '}';
        *json = allocateCString(sstr.str());
        return 0;
    }
    catch (std::exception const& exc)
    {
        WretchedCss::DisplayError(exc);
        return 1;
    }
}
//---------------------------------------------------------------------------------------------------------------------
C_LINKAGE DLL_EXPORT void free_buffer(char* buffer)
{
    delete buffer;
}
//---------------------------------------------------------------------------------------------------------------------
