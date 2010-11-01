#pragma once

#include <pslight/types.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VIDEO_RESOLUTION_1080	1
#define VIDEO_RESOLUTION_720	2
#define VIDEO_RESOLUTION_480	4
#define VIDEO_RESOLUTION_576	5

typedef struct {
	uint16_t width;
	uint16_t height;
} videoResolution;

typedef struct {
	uint8_t resolution;
	uint8_t scanMode; // Interlaced or Progressive
	uint8_t conversion;
	uint8_t aspect;
	uint8_t unknown[2];
	uint16_t refreshRates;
} videoDisplayMode;

#define VIDEO_STATE_DISABLED	0
#define VIDEO_STATE_ENABLED 	1
#define VIDEO_STATE_BUSY	3

typedef struct {
	uint8_t state;
	uint8_t colorSpace;
	uint8_t unknown[6];
	VideoDisplayMode* displayMode;
}

int videoGetResolution(int resolutionId, videoResolution* resolution);
int videoConfigure(int videoOut, int resolutionId, int option, int waitForEvent);
int videoGetState(int videoOut, int deviceIndex, VideoState *state);


#ifdef __cplusplus
}
#endif
