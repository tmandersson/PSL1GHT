#include <rsx/commands.h>
#include <rsx/nv40.h>
#include <rsx/buffer.h>

void realitySetClearColor(gcmContextData *context, uint32_t color) {
	commandBufferPutCmd1(context, NV30_3D_CLEAR_COLOR_VALUE, color);
}

void realityNop(gcmContextData *context) {
	commandBufferPutCmd1(context, 0x100, 0);
}

void realityClearBuffers(gcmContextData *context, uint32_t buffers) {
	commandBufferPutCmd1(context, NV30_3D_CLEAR_BUFFERS, buffers);
}	
/*
void realitySetRenderTarget(gcmContextData *context, realityTarget target) {
	
}
*/
void realitySetViewportOffset(gcmContextData *context, uint16_t x, uint16_t y) {
	commandBufferPutCmd1(context, NV30_3D_VIEWPORT_TX_ORIGIN, x | y << 16);
}

