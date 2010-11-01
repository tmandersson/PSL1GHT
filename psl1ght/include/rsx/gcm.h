/***
 * These are functions that are provided by libgcm_sys.sprx, which is the only
 * part of libgcm that we can legally use.
 */

#pragma once

#include <psl1ght/types.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

int gcmInitBody(void **contex, const uint32_t cmdSize, const uint32_t ioSize, const void* ioAddress);


#ifdef __cplusplus
}
#endif
