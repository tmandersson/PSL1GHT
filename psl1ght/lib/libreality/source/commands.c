#include <rsx/commands.h>
#include <rsx/nv40.h>

void realitySetClearColor(gcmContextData *context, uint32_t color) {
	if(checkCommandBufferLength(context, 8) == 0) {
		commandBufferPutCmd1(context, NV30_3D_CLEAR_COLOR_VALUE, color);
	}
}


int checkCommandBufferLength(gcmContextData *context, uint32_t len) {
	if (context->current + len > context->end) {
		int retval; // It's a bit messy, but it works.
		int tocval = ((uint32_t *)(uint64_t) context->callback)[1];
		int procaddr = ((uint32_t *)(uint64_t) context->callback)[0];
		asm("mr 3,%3; mr 31,2; mr 2,%1; mtctr %2; bctrl; mr 2,31; mr %0,3;" : "=r"(retval) : "r"(tocval), "r"(procaddr), "r"(context) : "r31", "r3");
		return retval;
	}
	return 0;
}

void commandBufferPut(gcmContextData* context, uint32_t value) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	 *buffer++ = value;
	context->current = (uint32_t)(uint64_t) buffer;
}

void inline commandBufferPutCmd1(gcmContextData* context, uint32_t command, uint32_t v1) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	*buffer++ = command | 1 << 18;
	*buffer++ = v1;
	context->current = (uint32_t)(uint64_t) buffer;
}

void inline commandBufferPutCmd2(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	*buffer++ = command | 2 << 18;
	*buffer++ = v1;
	*buffer++ = v2;
	context->current = (uint32_t)(uint64_t) buffer;
}

void inline commandBufferPutCmd3(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	*buffer++ = command | 3 << 18;
	*buffer++ = v1;
	*buffer++ = v2;
	*buffer++ = v3;
	context->current = (uint32_t)(uint64_t) buffer;
}

void inline commandBufferPutCmd4(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	*buffer++ = command | 4 << 18;
	*buffer++ = v1;
	*buffer++ = v2;
	*buffer++ = v3;
	*buffer++ = v4;
	context->current = (uint32_t)(uint64_t) buffer;
}

void inline commandBufferPutCmd5(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	*buffer++ = command | 5 << 18;
	*buffer++ = v1;
	*buffer++ = v2;
	*buffer++ = v3;
	*buffer++ = v4;
	*buffer++ = v5;
	context->current = (uint32_t)(uint64_t) buffer;
}

void inline commandBufferPutCmd6(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, uint32_t v6) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	*buffer++ = command | 6 << 18;
	*buffer++ = v1;
	*buffer++ = v2;
	*buffer++ = v3;
	*buffer++ = v4;
	*buffer++ = v5;
	*buffer++ = v6;
	context->current = (uint32_t)(uint64_t) buffer;
}

void inline commandBufferPutCmd7(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, uint32_t v6, uint32_t v7) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	*buffer++ = command | 7 << 18;
	*buffer++ = v1;
	*buffer++ = v2;
	*buffer++ = v3;
	*buffer++ = v4;
	*buffer++ = v5;
	*buffer++ = v6;
	*buffer++ = v7;
	context->current = (uint32_t)(uint64_t) buffer;
}

void inline commandBufferPutCmd8(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, uint32_t v6, uint32_t v7, uint32_t v8) {
	uint32_t* buffer = (uint32_t *)(uint64_t) context->current;
	*buffer++ = command | 8 << 18;
	*buffer++ = v1;
	*buffer++ = v2;
	*buffer++ = v3;
	*buffer++ = v4;
	*buffer++ = v5;
	*buffer++ = v6;
	*buffer++ = v7;
	*buffer++ = v8;
	context->current = (uint32_t)(uint64_t) buffer;
}



