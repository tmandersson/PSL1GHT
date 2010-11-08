#pragma once

#include <rsx/gcm.h>

#ifdef __cplusplus
extern "C" {
#endif

// Set the colour for clearing buffers, should be in ARGB format.
void realitySetClearColor(gcmContextData *context, uint32_t color);

// For actually clearing the bufders
#define CLEAR_BUFFERS_DEPTH				0x00000001
#define CLEAR_BUFFERS_STENCIL				0x00000002
#define CLEAR_BUFFERS_COLOR_R				0x00000010
#define CLEAR_BUFFERS_COLOR_G				0x00000020
#define CLEAR_BUFFERS_COLOR_B				0x00000040
#define CLEAR_BUFFERS_COLOR_A				0x00000080
void realityClearBuffers(gcmContextData *context, uint32_t buffers);

// For when you need to do nothing
void realityNop(gcmContextData *context);

#define LOCATION_RSX_MEMORY	0
#define LOCATION_CELL_MEMORY	1

enum surfaces {REALITY_SURFACE_COLOR0, REALITY_SURFACE_COLOR1, REALITY_SURFACE_COLOR2, 
		REALITY_SUFACE_COLOR3, REALITY_SURFACE_ZETA};
void realitySetupRenderSurface(gcmContextData *context, uint8_t sufrace, uint8_t location, uint32_t offset, uint32_t pitch);

#define TARGET_NONE	0x00 /* Don't render anything */
#define TARGET_0	0x01 /* Render to color surface 0 */
#define TARGET_1	0x02 /* Render to color surface 1 */
#define	TARGET_MRT1	0x13 /* Render to both color surfaces 0 and 1 */
#define	TARGET_MRT2	0x17 /* Render to color surface 0, 1 and 2 */
#define	TARGET_MRT3	0x1F /* Render to color surface 0, 1, 2 and 3 */

#define TARGET_FORMAT_COLOR_X1R5G5B5			0x00000001
#define TARGET_FORMAT_COLOR_R5G6B5			0x00000003
#define TARGET_FORMAT_COLOR_X8R8G8B8			0x00000005
#define TARGET_FORMAT_COLOR_A8R8G8B8			0x00000008
#define TARGET_FORMAT_COLOR_B8				0x00000009
#define TARGET_FORMAT_COLOR_A16B16G16R16_FLOAT		0x0000000b
#define TARGET_FORMAT_COLOR_A32B32G32R32_FLOAT		0x0000000c
#define TARGET_FORMAT_COLOR_R32_FLOAT			0x0000000d
#define TARGET_FORMAT_COLOR_X8B8G8R8			0x0000000f
#define TARGET_FORMAT_COLOR_A8B8G8R8			0x00000010

#define TARGET_FORMAT_ZETA_Z16				0x00000020
#define TARGET_FORMAT_ZETA_Z24S8			0x00000040

#define TARGET_FORMAT_TYPE_LINEAR			0x00000100
#define TARGET_FORMAT_TYPE_SWIZZLED			0x00000200

#define TARGET_FORMAT_MSAA_NONE				0x00000000
#define TARGET_FORMAT_MSAA_2X				0x00003000
#define TARGET_FORMAT_MSAA_4X				0x00004000
#define TARGET_FORMAT_MSAA_4X_ROTATED			0x00005000

void realitySelectRenderTarget(gcmContextData *context, uint8_t target, uint32_t format, 
				uint16_t width, uint16_t height, uint16_t x, uint16_t y);

#ifdef __cplusplus
}
#endif
