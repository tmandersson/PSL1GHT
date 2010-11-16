
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

#include <rsx/commands.h>
#include <rsx/nv40.h>

#include <io/pad.h>

#include <sysmodule/sysmodule.h>

#include "ball.bin.h"
#include "texture.h"
#include "rsxutil.h"
#include "nv_shaders.h"

int currentBuffer = 0;
realityTexture *ball; // Texture.

void drawFrame(int buffer, long frame) {

	setupRenderTarget(buffer);

	realityViewportTranslate(context, 0.0, 0.0, 0.0, 0.0);
	realityViewportScale(context, 1.0, 1.0, 1.0, 0.0); 

	realityZControl(context, 0, 1, 1); // disable viewport culling

	// Enable alpha blending.
	realityBlendFunc(context,
		NV30_3D_BLEND_FUNC_SRC_RGB_SRC_ALPHA |
		NV30_3D_BLEND_FUNC_SRC_ALPHA_SRC_ALPHA,
		NV30_3D_BLEND_FUNC_DST_RGB_ONE_MINUS_SRC_ALPHA |
		NV30_3D_BLEND_FUNC_DST_ALPHA_ZERO);
	realityBlendEquation(context, NV40_3D_BLEND_EQUATION_RGB_FUNC_ADD |
		NV40_3D_BLEND_EQUATION_ALPHA_FUNC_ADD);
	realityBlendEnable(context, 1);

	realityViewport(context, res.width, res.height);

	// Just because we can only set the clear color, dosen't mean it has to be boring
	double cycle = (frame % 200)/100.0;
	uint8_t color = (sin(cycle*M_PI) + 1.0) * 127 ;

	// set the clear color
	realitySetClearColor(context, color << 8 | color << 16); 
	// and the depth clear value
	realitySetClearDepthValue(context, 0xffff);
	// Clear the buffers
	realityClearBuffers(context, REALITY_CLEAR_BUFFERS_COLOR_R |
				     REALITY_CLEAR_BUFFERS_COLOR_G |
				     REALITY_CLEAR_BUFFERS_COLOR_B |
				     REALITY_CLEAR_BUFFERS_DEPTH);

	realityLoadVertexProgram(context, &nv40_vp);
	realityLoadFragmentProgram(context, &nv30_fp);
}

void unload_modules() {
	SysUnloadModule(SYSMODULE_PNGDEC);
	SysUnloadModule(SYSMODULE_FS);
}

s32 main(s32 argc, const char* argv[])
{
	PadInfo padinfo;
	PadData paddata;
	int i;
	
	init_screen();
	ioPadInit(7);

	atexit(unload_modules);

	// Load png decoder
	assert(SysLoadModule(SYSMODULE_FS) != 0);
	assert(SysLoadModule(SYSMODULE_PNGDEC) != 0);

	// Load texture
	ball = loadTexture(ball_bin);

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
		drawFrame(currentBuffer, frame++); // Draw into the unused buffer
		flip(currentBuffer); // Flip buffer onto screen
		currentBuffer = !currentBuffer;
	}
	
	return 0;
}

