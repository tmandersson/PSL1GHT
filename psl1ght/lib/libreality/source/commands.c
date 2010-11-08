#include <rsx/commands.h>
#include <rsx/nv40.h>
#include <rsx/buffer.h>

void realitySetClearColor(gcmContextData *context, uint32_t color) {
	COMMAND_LENGTH(context, 0x8);
	commandBufferPutCmd1(context, NV30_3D_CLEAR_COLOR_VALUE, color);
}

void realityNop(gcmContextData *context) {
	COMMAND_LENGTH(context, 0x8);
	commandBufferPutCmd1(context, 0x100, 0);
}

void realityClearBuffers(gcmContextData *context, uint32_t buffers) {
	COMMAND_LENGTH(context, 0x8);
	commandBufferPutCmd1(context, NV30_3D_CLEAR_BUFFERS, buffers);
}	

void realitySetDmaLocation(gcmContextData *context, uint8_t color0, uint8_t color1, uint8_t color2, uint8_t color3, uint8_t zeta) {
	COMMAND_LENGTH(context, 0x20);
	// Setup DMA handles
	commandBufferPutCmd1(context, NV30_3D_DMA_COLOR1, color1 | 0xFEED0000);
	commandBufferPutCmd2(context, NV30_3D_DMA_COLOR0, 0xFEED0000 | color0, 0xFEED0000 | zeta);
	commandBufferPutCmd2(context, NV40_3D_DMA_COLOR2, 0xFEED0000 | color2, 0xFEED0000 | color3);
}

void realitySetViewportOffset(gcmContextData *context, uint16_t x, uint16_t y) {
	COMMAND_LENGTH(context, 0x8);
	commandBufferPutCmd1(context, NV30_3D_VIEWPORT_TX_ORIGIN, x | y << 16);
}

