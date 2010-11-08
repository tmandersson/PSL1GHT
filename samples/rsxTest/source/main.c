/* Now double buffered with animation.
 */ 

#include <psl1ght/lv2.h>

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include <sysutil/video.h>
#include <rsx/gcm.h>
#include <rsx/reality.h>
#include <rsx/commands.h>

#include <io/pad.h>

#include <psl1ght/lv2.h>

gcmContextData *context; // Context to keep track of the RSX buffer.

VideoResolution res; // Screen Resolution

int currentBuffer = 0;
s32 *buffer[3]; // The buffer we will be drawing into
u32 offset[3]; // The offset of the buffers in RSX memory
int pitch;

void waitFlip() { // Block the PPU thread untill the previous flip operation has finished.
	while(gcmGetFlipStatus() != 0) 
		usleep(200);
	gcmResetFlipStatus();
}

void flip(s32 buffer) {
	assert(gcmSetFlip(context, buffer) == 0);
	realityFlushBuffer(context);
	gcmSetWaitFlip(context); // Prevent the RSX from continuing until the flip has finished.
}

// Initilize everything. You can probally skip over this function.
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

	// Get the current resolution
	assert(videoGetResolution(state.displayMode.resolution, &res) == 0);
	
	pitch = 4 * res.width; // each pixel is 4 bytes

	// Configure the buffer format to xRGB
	VideoConfiguration vconfig;
	memset(&vconfig, 0, sizeof(VideoConfiguration));
	vconfig.resolution = state.displayMode.resolution;
	vconfig.format = VIDEO_BUFFER_FORMAT_XRGB;
	vconfig.pitch = pitch;

	assert(videoConfigure(0, &vconfig, NULL, 0) == 0);
	assert(videoGetState(0, 0, &state) == 0); 

	s32 buffer_size = pitch * res.height; 
	printf("buffers will be 0x%x bytes\n", buffer_size);
	
	gcmSetFlipMode(GCM_FLIP_VSYNC); // Wait for VSYNC to flip

	// Allocate two buffers for the RSX to draw to the screen (double buffering)
	buffer[0] = rsxMemAlign(16, buffer_size);
	buffer[1] = rsxMemAlign(16, buffer_size);
	buffer[2] = rsxMemAlign(16, buffer_size);
	assert(buffer[0] != NULL && buffer[1] != NULL);

	assert(realityAddressToOffset(buffer[0], &offset[0]) == 0);
	assert(realityAddressToOffset(buffer[1], &offset[1]) == 0);
	assert(realityAddressToOffset(buffer[2], &offset[2]) == 0);
	// Setup the display buffers
	assert(gcmSetDisplayBuffer(0, offset[0], pitch, res.width, res.height) == 0);
	assert(gcmSetDisplayBuffer(1, offset[1], pitch, res.width, res.height) == 0);

	realitySetRenderSurface(context, REALITY_SURFACE_COLOR0, REALITY_LOCATION_RSX_MEMORY, 
					offset[0], pitch);
	realitySetRenderSurface(context, REALITY_SURFACE_ZETA, REALITY_LOCATION_RSX_MEMORY, 
					offset[2], pitch);


	realitySelectRenderTarget(context, REALITY_TARGET_0, 
		REALITY_TARGET_FORMAT_COLOR_X8R8G8B8 | REALITY_TARGET_FORMAT_ZETA_Z24S8 | REALITY_TARGET_FORMAT_TYPE_LINEAR,
		res.width, res.height, 0, 0);

	gcmResetFlipStatus();
	flip(1);
}

void drawFrame(int *buffer, long frame) {
	realitySetRenderSurface(context, REALITY_SURFACE_COLOR0, REALITY_LOCATION_RSX_MEMORY, 
					offset[currentBuffer], pitch);
	realitySetClearColor(context, 0x88FF0088);
	realityClearBuffers(context, REALITY_CLEAR_BUFFERS_COLOR_R |
				     REALITY_CLEAR_BUFFERS_COLOR_G |
				     REALITY_CLEAR_BUFFERS_COLOR_B |
				     REALITY_CLEAR_BUFFERS_COLOR_A);
}

s32 main(s32 argc, const char* argv[])
{
	PadInfo padinfo;
	PadData paddata;
	int i;
	
	init_screen();
	ioPadInit(7);

	long frame = 0; // To keep track of how many frames we have rendered.
	
	// Ok, everything is setup. Now for the main loop.
	while(1){
		// Check the pads.
		ioPadGetInfo(&padinfo);
		for(i=0; i<MAX_PADS; i++){
			if(padinfo.status[i]){
				ioPadGetData(i, &paddata);
				
				if(paddata.BTN_CROSS){
					return 0;
				}
			}
			
		}

		waitFlip(); // Wait for the last flip to finish, so we can draw to the old buffer
		drawFrame(buffer[currentBuffer], frame++); // Draw into the unused buffer
		flip(currentBuffer); // Flip buffer onto screen
		currentBuffer = !currentBuffer;
	}
	
	return 0;
}

