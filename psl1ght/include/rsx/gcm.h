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

#define GCM_FLIP_VSYNC 2
#define GCM_FLIP_HSYNC 1
#define GCM_FLIP_HSYNC_AND_BREAK_EVERYTHING 3
void gcmSetFlipMode(int mode);

typedef struct {
	uint32_t localAddress;
	uint32_t ioAddress;
	int localSize;
	int ioSize;
	int memoryFreq;
	int coreFreq;
} gcmConfiguration;

void gcmGetConfigturation(gcmConfiguration *config);



#ifdef __cplusplus
}
#endif
