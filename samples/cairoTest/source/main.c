/* Note: this example only has a single buffer so it is only possible
 * 	 to draw a single image to the screen.
 * 	 if you want animation you will need a second buffer and to flip
 * 	 between them.
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

#include <io/pad.h>

#include <psl1ght/lv2.h>

#include <cairo/cairo.h>
#include "testpng.bin.h"
#include "draw.h"

#include <math.h>

gcmContextData *context; // Context to keep track of the RSX buffer.

VideoResolution res; // Screen Resolution

struct image *image;

int currentBuffer = 0;
buffer *buffers[2]; // The buffer we will be drawing into.

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

void makeBuffer(int id, int size) {
	buffer *buf = malloc(sizeof(buffer));
	buf->ptr = rsxMemAlign(16, size);
	assert(buf->ptr != NULL);

	assert(realityAddressToOffset(buf->ptr, &buf->offset) == 0);
	// Register the display buffer with the RSX
	assert(gcmSetDisplayBuffer(id, buf->offset, res.width * 4, res.width, res.height) == 0);
	
	buf->width = res.width;
	buf->height = res.height;
	buffers[id] = buf;
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
	
	// Configure the buffer format to xRGB
	VideoConfiguration vconfig;
	memset(&vconfig, 0, sizeof(VideoConfiguration));
	vconfig.resolution = state.displayMode.resolution;
	vconfig.format = VIDEO_BUFFER_FORMAT_XRGB;
	vconfig.pitch = res.width * 4;

	assert(videoConfigure(0, &vconfig, NULL, 0) == 0);
	assert(videoGetState(0, 0, &state) == 0); 

	s32 buffer_size = 4 * res.width * res.height; // each pixel is 4 bytes
	printf("buffers will be 0x%x bytes\n", buffer_size);
	
	gcmSetFlipMode(GCM_FLIP_VSYNC); // Wait for VSYNC to flip

	// Allocate two buffers for the RSX to draw to the screen (double buffering)
	makeBuffer(0, buffer_size);
	makeBuffer(1, buffer_size);

	gcmResetFlipStatus();
	flip(1);
}

void drawFrame(buffer *buffer, long frame) {
	cairo_t *cr;

	cairo_surface_t *surface = cairo_image_surface_create_for_data((u8 *) buffer->ptr, 
		CAIRO_FORMAT_RGB24, buffer->width, buffer->height, buffer->width * 4);
	assert(surface != NULL);
	cr = cairo_create(surface);
	assert(cr != NULL);

	// Lets start by clearing everything
	cairo_rectangle(cr, 0, 0, buffer->width, buffer->height);
	cairo_set_source_rgb (cr, 1.0, 1.0, 1.0); // White
	//cario_fill(cr);

	cairo_set_line_width(cr, 10.0);
	cairo_set_source_rgb (cr, 1.0, 0.5, 0.0); // Yellow, maybe
	cairo_arc(cr, 128.0, 128.0, 76.0, 0, 2*M_PI);
	cairo_stroke(cr);

	cairo_destroy(cr); // Realease Surface
	cairo_surface_finish(surface);
	cairo_surface_destroy(surface); // Flush and destroy the cairo surface
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
		drawFrame(buffers[currentBuffer], frame++); // Draw into the unused buffer
		flip(currentBuffer); // Flip buffer onto screen
		currentBuffer = !currentBuffer;
	}
	
	return 0;
}

