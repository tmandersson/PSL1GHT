#include <psl1ght/lv2.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <sysutil/video.h>
#include <rsx/gcm.h>
#include <rsx/reality.h>

#include <io/pad.h>

#include <psl1ght/lv2.h>

gcmContextData *context;

VideoResolution res;
int aspect;
int *rsx_memory;

void waitFlip() {
	while(gcmGetFlipStatus() != 0) 
		usleep(200);
	gcmResetFlipStatus();
}

void flip(int buffer) {
	assert(gcmSetFlip(context, buffer) == 0);
	realityFlushBuffer(context);
	gcmSetWaitFlip(context); // Block until flip has finished
}

void init_screen() {
	// Allocate a 1Mb buffer, alligned to a 1Mb boundary to be our shared IO memory with the RSX.
	void *host_addr = memalign(1024*1024, 1024*1024);
	assert(host_addr != NULL);

	// Initilise Reality, which sets up the command buffer and shared IO memory
	context = realityInit(0x10000, 1024*1024, host_addr); 
	assert(context != NULL);

	VideoState state;
	assert(videoGetState(0, 0, &state) == 0); // Get the state of the display

	assert(state.state == 0); // Make sure display is enabled

	assert(videoGetResolution(state.displayMode.resolution, &res) == 0);

	
	// Setup the video stuff 
	VideoConfiguration vconfig;
	memset(&vconfig, 0, sizeof(VideoConfiguration));
	vconfig.resolution = state.displayMode.resolution;
	vconfig.format = VIDEO_BUFFER_FORMAT_XRGB;
	vconfig.pitch = res.width * 4;

	assert(videoConfigure(0, &vconfig, NULL, 0) == 0);

	assert(videoGetState(0, 0, &state) == 0); 

	if(state.displayMode.aspect == VIDEO_ASPECT_4_3) { // Aspect might be useful too
		aspect = 4.0/3.0;
	} else { 
		aspect = 16.0/9.0;
	}

	int buffer_size = 4 * res.width * res.height; // each pixel is 4 bytes
	printf("buffers will be 0x%x bytes\n", buffer_size);
	
	gcmSetFlipMode(GCM_FLIP_VSYNC);

	gcmConfiguration config;
	gcmGetConfiguration(&config);

	int *buffer = realityAllocateAlignedRsxMemory(16, buffer_size);
	assert(buffer != NULL);

	// Fill the display buffer with something pretty
	int i, j;
	for(i = 0; i < res.height; i++) {
		int color = (i / (res.height * 1.0) * 256);
		color = (color << 8); // This should make a nice green graident
		for(j = 0; j < res.width; j++) buffer[i* res.width + j] = color;
	}

	uint32_t offset;
	assert(realityAddressToOffset(buffer, &offset) == 0);

	printf("Offset in RSX memory is 0x%08x\n", offset);

	assert(gcmSetDisplayBuffer(0, offset, res.width * 4, res.width, res.height) == 0);
	gcmResetFlipStatus();
	printf("ok, lets try flipping the buffer onto the screen\n");
	
	flip(0);
	waitFlip();
	// And we need to flip again because for some reason our first flip is swallowed
	flip(0);

	printf("There should now be something on the screen\n");
}

int main(int argc, const char* argv[])
{
	init_screen();

	ioPadInit(7);

	sleep(30);
	
	printf("exiting\n");

	return 0;
}

