#include <psl1ght/lv2.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>


#include <sysutil/video.h>
#include <rsx/gcm.h>

#include <psl1ght/lv2.h>

gcmContextData *context;

int screen_width;
int screen_height;
int aspect;
int *rsx_memory;

void flushBuffer(gcmContextData *context) {
	gcmControlRegister *control = gcmGetControlRegister(context);
	__asm __volatile__("sync"); // Sync, to make sure the command was written;
	int offset;
	gcmAddressToOffset(context->current, &offset);
	control->put = offset;
}

void waitFlip() {
	while(gcmGetFlipStatus() != 0) 
		usleep(200);
	gcmResetFlipStatus();
}

void flip(int buffer) {
	assert(gcmSetFlip(context, buffer) == 0);
	flushBuffer(context);
	gcmSetWaitFlip(context); // Block until flip has finished
}

void init_screen() {
	int ret;
	
	VideoState state;
	ret = videoGetState(0, 0, &state); // Get the state of the display

	assert(ret == 0);
	assert(state.state == 0); // Make sure display is enabled

	VideoResolution res;
	videoGetResolution(state.displayMode.resolution, &res);
	assert(ret == 0);

	screen_width = res.width; 
	screen_height = res.height; // Save resolution for later

	VideoConfiguration vconfig;
	memset(&vconfig, 0, sizeof(VideoConfiguration));
	vconfig.resolution = state.displayMode.resolution;
	vconfig.format = VIDEO_BUFFER_FORMAT_XRGB;
	vconfig.pitch = screen_width * 4;

	assert(videoConfigure(0, &vconfig, NULL, 0) == 0);

	assert(videoGetState(0, 0, &state) == 0); 

	if(state.displayMode.aspect == VIDEO_ASPECT_4_3) { // Aspect might be useful too
		aspect = 4.0/3.0;
	} else { 
		aspect = 16.0/9.0;
	}

	int buffer_size = 4 * screen_width * screen_height; // each pixel is 4 bytes
	printf("buffers will be 0x%x bytes\n", buffer_size);
	
	gcmSetFlipMode(GCM_FLIP_VSYNC);

	gcmConfiguration config;
	gcmGetConfiguration(&config);

	printf("localMemory:\t0x%08x-%08x\nioMemory:\t0x%08x-%08x\n",
		config.localAddress, config.localAddress + config.localSize,
		config.ioAddress, config.ioAddress + config.ioSize);

	printf("Frequencys:\n\tcore:\t%i\n\tmemory:\t%i\n",
		config.coreFreq, config.memoryFreq);

	rsx_memory = (unsigned int *) config.localAddress;

	// Fill the display buffer with something pretty
	int i, j;
	for(i = 0; i < screen_height; i++) {
		int color = (i / (screen_height * 1.0) * 256);
		color = (color << 8); // This should make a nice green graident
		for(j = 0; j < screen_width; j++) rsx_memory[i* screen_width + j] = color;
	}

	int offset;
	assert(gcmAddressToOffset((uint32_t) rsx_memory, &offset) == 0);

	printf("Offset in RSX memory is 0x%08x\n", offset);

	assert(gcmSetDisplayBuffer(0, offset, screen_width * 4, screen_width, screen_height) == 0);
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
	int ret;
	void *host_addr = memalign(1024*1024, 1024*1024); // Allocate a 1Mb buffer, alligned to a 1mb boundary.
	assert(host_addr != 0);

	printf("Allocated 1Mb buffer @ 0x%08lx\n", (long) host_addr);

	uint32_t temp_context = 0;

	ret = gcmInitBody(&temp_context, 0x10000, 1024*1024, host_addr); 
	context = temp_context; 
	printf("gcmInitBody(), ret=0x%x, context=0x%08x\n", ret, temp_context);
	assert(ret == 0);

	init_screen();

	sleep(30);
	
	printf("exiting\n");

	return 0;
}

