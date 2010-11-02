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

typedef struct{
	uint32_t begin;
	uint32_t end;
	uint32_t current;
	uint32_t callback;
} gcmContextData;

int gcmInitBody(uint32_t *contex, const uint32_t cmdSize, const uint32_t ioSize, const void* ioAddress);

#define GCM_FLIP_VSYNC 2
#define GCM_FLIP_HSYNC 1
#define GCM_FLIP_HSYNC_AND_BREAK_EVERYTHING 3
void gcmSetFlipMode(int mode);

typedef struct {
	uint32_t localAddress;
	uint32_t ioAddress;
	int32_t localSize;
	int32_t ioSize;
	int32_t memoryFreq;
	int32_t coreFreq;
} gcmConfiguration;

void gcmGetConfiguration(gcmConfiguration *config);

int gcmAddressToOffset(uint32_t address, uint32_t *offset);

int gcmSetDisplayBuffer(uint32_t bufferId, uint32_t offset, uint32_t pitch, uint32_t width, uint32_t height);
int gcmSetFlip(gcmContextData *context, uint32_t bufferId);
void gcmSetWaitFlip(gcmContextData *context);
int gcmGetFlipStatus();
void gcmResetFlipStatus();

typedef struct {
	uint32_t put;
	uint32_t get;
	uint32_t ref;
} gcmControlRegister;

gcmControlRegister *gcmGetControlRegister();
void gcmFlushBuffer(gcmContextData *context);

#ifdef __cplusplus
}
#endif
