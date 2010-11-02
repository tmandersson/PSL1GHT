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
	int localSize;
	int ioSize;
	int memoryFreq;
	int coreFreq;
} gcmConfiguration;

void gcmGetConfiguration(gcmConfiguration *config);
int gcmAddressToOffset(int address, int *offset);

int gcmSetDisplayBuffer(int id, int offset, int pitch, int width, int height);
int gcmSetFlip(gcmContextData *context, int id);
void gcmSetWaitFlip(gcmContextData *context);
int gcmGetFlipStatus();
void gcmResetFlipStatus();

typedef struct {
	uint32_t put;
	uint32_t get;
	uint32_t ref;
} gcmControlRegister;

gcmControlRegister *gcmGetControlRegister(gcmContextData *context);

#ifdef __cplusplus
}
#endif
