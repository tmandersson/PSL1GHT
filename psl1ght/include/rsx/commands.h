#pragma once

#include <rsx/gcm.h>

#ifdef __cplusplus
extern "C" {
#endif

// Set the colour for clearing buffers, should be in ARGB format.
void realitySetClearColor(gcmContextData *context, uint32_t color);



// Internal function that you shouldn't use unless you are directly manulipting the buffer.
int checkCommandBufferLength(gcmContextData *context, uint32_t len);
void commandBufferPut(gcmContextData *context, uint32_t value);

#ifdef __cplusplus
}
#endif
