#pragma once

#include <psl1ght/types.h>

#include "rsx/gcm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* realityFlushBuffer:
 * Flushes the RSX Command buffer.
 */
void realityFlushBuffer(gcmContextData *context);

/* realityInit:
 * Maps the memory at ioAddress into the RSX's memory space so the userspace thread
 * and the RSX can comunicate.
 * This shared memory must be 1mb aligned, and at least 1mb long.
 * Also Initilizes a RSX command buffer of cmdSize inside the shared memory. 
 * 
 * Returns a context structure that controls the current status of thecommand buffer.
 */
gcmContextData *realityInit(const uint32_t cmdSize, const uint32_t ioSize, const void* ioAddress);

int realityAddressToOffset(void *ptr, uint32_t *offset);

void *realityAllocateAlignedRsxMemory(int alignment, int size);

void *realityAllocateRsxMemory(int size);

#ifdef __cplusplus
}
#endif
