#pragma once

#include <rsx/gcm.h>

#ifdef __cplusplus
extern "C" {
#endif

// Set the colour for clearing buffers, should be in ARGB format.
void realitySetClearColor(gcmContextData *context, uint32_t color);

// For actually clearing the bufders
void realityClearBuffers(gcmContextData *context, uint32_t buffers);


// For when you need to do nothing
void realityNop(gcmContextData *context);

// Internal function that you shouldn't use unless you are directly manulipting the buffer.
int checkCommandBufferLength(gcmContextData *context, uint32_t len);
void commandBufferPut(gcmContextData *context, uint32_t value);

void inline commandBufferPutCmd1(gcmContextData* context, uint32_t command, uint32_t v1);
void inline commandBufferPutCmd2(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2);
void inline commandBufferPutCmd3(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3); 
void inline commandBufferPutCmd4(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4);
void inline commandBufferPutCmd5(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5);
void inline commandBufferPutCmd6(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, uint32_t v7);
void inline commandBufferPutCmd7(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, uint32_t v6, uint32_t v7);
void inline commandBufferPutCmd8(gcmContextData* context, uint32_t command, uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4, uint32_t v5, uint32_t v6, uint32_t v7, uint32_t v8);

#ifdef __cplusplus
}
#endif
