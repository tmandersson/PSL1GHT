#include <rsx/commands.h>
#include <rsx/nv40.h>
#include <rsx/buffer.h>

void realitySetClearColor(gcmContextData *context, uint32_t color) {
	COMMAND_LENGTH(context, 2);
	commandBufferPutCmd1(context, NV30_3D_CLEAR_COLOR_VALUE, color);
}

void realityNop(gcmContextData *context) {
	COMMAND_LENGTH(context, 2);
	commandBufferPutCmd1(context, 0x100, 0);
}

void realityClearBuffers(gcmContextData *context, uint32_t buffers) {
	COMMAND_LENGTH(context, 4);
	commandBufferPutCmd1(context, NV30_3D_CLEAR_BUFFERS, buffers);
	commandBufferPutCmd1(context, 0x100, 0); // Nop
}	

const static uint32_t offset_cmds[] = {NV30_3D_COLOR0_OFFSET, NV30_3D_COLOR1_OFFSET,
		NV40_3D_COLOR2_OFFSET, NV40_3D_COLOR3_OFFSET, NV30_3D_ZETA_OFFSET};
const static uint32_t dma_cmds[] = {NV30_3D_DMA_COLOR0, NV30_3D_DMA_COLOR1,
		NV40_3D_DMA_COLOR2, NV40_3D_DMA_COLOR3, NV30_3D_DMA_ZETA};
const static uint32_t pitch_cmds[] = {NV30_3D_COLOR0_PITCH, NV30_3D_COLOR1_PITCH,
		NV40_3D_COLOR2_PITCH, NV40_3D_COLOR3_PITCH, NV40_3D_ZETA_PITCH};

void realitySetRenderSurface(gcmContextData *context, uint8_t surface, uint8_t location,
				uint32_t offset, uint32_t pitch) {
	COMMAND_LENGTH(context, 6);
	commandBufferPutCmd1(context, dma_cmds[surface], location | 0xFEED0000);
	commandBufferPutCmd1(context, offset_cmds[surface], offset);
	commandBufferPutCmd1(context, pitch_cmds[surface], pitch);
}

void realitySelectRenderTarget(gcmContextData *context, uint8_t target, uint32_t format, 
				uint16_t width, uint16_t height, uint16_t x, uint16_t y) {
	COMMAND_LENGTH(context, 11);

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
	COMMAND_LENGTH(context, 2);
	commandBufferPutCmd1(context, NV30_3D_VIEWPORT_TX_ORIGIN, x | y << 16);
}

void realityVertexBegin(gcmContextData *context, uint32_t type) {
	COMMAND_LENGTH(context, 2);
	commandBufferPutCmd1(context, NV30_3D_VERTEX_BEGIN_END, type);
}

void realityVertexEnd(gcmContextData *context) {
	COMMAND_LENGTH(context, 2);
	commandBufferPutCmd1(context, NV30_3D_VERTEX_BEGIN_END, NV30_3D_VERTEX_BEGIN_END_STOP);
}

void realityVertex4f(gcmContextData *context, float x, float y, float z, float w) {
	COMMAND_LENGTH(context, 5);
	commandBufferPutCmd4(context, NV30_3D_VTX_ATTR_4F(0),
				 ((ieee32) x).u, 
				 ((ieee32) y).u,
				 ((ieee32) z).u, 
				 ((ieee32) w).u);
}

void realityLoadVertexProgram(gcmContextData *context, realityVertexProgram *prog) {
	int inst, command_size = prog->size * 2 + 7;
	COMMAND_LENGTH(context, command_size);
	
	commandBufferPutCmd1(context, NV30_3D_VP_UPLOAD_FROM_ID, 0);
	
	for(inst = 0; inst < prog->size; inst += 4) {
		commandBufferPutCmd4(context, NV30_3D_VP_UPLOAD_INST(inst), 
					prog->data[inst + 0],
					prog->data[inst + 1],
					prog->data[inst + 2],
					prog->data[inst + 3]);
	}

	commandBufferPutCmd1(context, NV30_3D_VP_START_FROM_ID, 0);
	commandBufferPutCmd2(context, NV40_3D_VP_ATTRIB_EN, prog->in_reg, prog->out_reg);

}

