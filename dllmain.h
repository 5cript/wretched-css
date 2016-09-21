#pragma once

#include "dll.h"

#include <stdint.h>

typedef int32_t result_type;

/**
 *  Used to free buffers, that were allocated by this library.
 *
 *  @param buffer A string buffer to deallocate.
 */
C_LINKAGE DLL_EXPORT void free_buffer(char* buffer);

/**
 *  Converts wiki markup to json.
 *
 *  @param css A null terminated string of valid css.
 *  @param json Will allocate memory and place a json string at its location.
 */
C_LINKAGE DLL_EXPORT void css_to_json(const char* css, char** json);

/**
 *  Converts json to wiki markup.
 *
 *  @param json A null terminated string of json.
 *  @param css Will allocate memory and place a css string at its location.
 */
C_LINKAGE DLL_EXPORT void json_to_css(const char* json, char** css);

/**
 *  Converts a css selector string int json (of WretchedCss::Selector type).
 *
 *  @param selector A valid css selector.
 *  @param json Will allocate memory and place a json string at its location.
 */
C_LINKAGE DLL_EXPORT result_type selector_to_json(const char* selector, char** json);
