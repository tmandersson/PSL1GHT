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

const static uint32_t offset_cmds[] = {NV30_3D_COLOR0_OFFSET, NV30_3D_COLOR1_OFFSET,
		NV40_3D_COLOR2_OFFSET, NV40_3D_COLOR3_OFFSET, NV30_3D_ZETA_OFFSET};
const static uint32_t dma_cmds[] = {NV30_3D_DMA_COLOR0, NV30_3D_DMA_COLOR1,
		NV40_3D_DMA_COLOR2, NV40_3D_DMA_COLOR3, NV30_3D_DMA_ZETA};
const static uint32_t pitch_cmds[] = {NV30_3D_COLOR0_PITCH, NV30_3D_COLOR1_PITCH,
		NV40_3D_COLOR2_PITCH, NV40_3D_COLOR3_PITCH, NV40_3D_ZETA_PITCH};

void realitySetRenderSurface(gcmContextData *context, uint8_t surface, uint8_t location,
				uint32_t offset, uint32_t pitch) {
	COMMAND_LENGTH(context, 0x18);
	commandBufferPutCmd1(context, dma_cmds[surface], location | 0xFEED0000);
	commandBufferPutCmd1(context, offset_cmds[surface], offset);
	commandBufferPutCmd1(context, pitch_cmds[surface], pitch);
}

void realitySelectRenderTarget(gcmContextData *context, uint8_t target, uint32_t format, 
				uint16_t width, uint16_t height, uint16_t x, uint16_t y) {
	COMMAND_LENGTH(context, 0x2c);

	format |= (31 - __builtin_clz(width)) << 16;
	format |= (31 - __builtin_clz(height)) << 24;
	uint32_t conventions = height | 0x1000; // COORD_CONVENTIONS_ORIGIN_INVERTED
	
	commandBufferPutCmd1(context, NV30_3D_RT_FORMAT, format); 
	commandBufferPutCmd1(context, NV30_3D_RT_ENABLE, target);
	commandBufferPutCmd1(context, NV30_3D_VIEWPORT_TX_ORIGIN, x | y << 16);
	commandBufferPutCmd1(context, NV30_3D_COORD_CONVENTIONS, conventions);
	commandBufferPutCmd2(context, NV30_3D_RT_HORIZ, x | width << 16, y | height << 16);
}

void realitySetViewportOffset(gcmContextData *context, uint16_t width, uint16_t height, uint16_t x, uint16_t y) {
	COMMAND_LENGTH(context, 0x8);
	commandBufferPutCmd1(context, NV30_3D_VIEWPORT_TX_ORIGIN, x | y << 16);
}

