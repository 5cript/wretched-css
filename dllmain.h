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
