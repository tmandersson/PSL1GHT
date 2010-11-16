#include <assert.h>
#include <string.h>

#include <pngdec/loadpng.h>

#include <rsx/reality.h>
#include <rsx/commands.h>
#include <rsx/nv40.h>

#include "texture.h"

realityTexture *loadTexture(const uint8_t *pngData) {
	PngDatas png;
	png.png_in= (void *) pngData;
	png.png_size= sizeof(pngData);

	LoadPNG(&png, NULL);

	realityTexture *tex = malloc(sizeof(realityTexture));

	uint32_t size = png.width * png.height * 4;
	uint32_t *textureAddress = rsxMemAlign(16, size);
	assert(textureAddress != NULL);
	assert(realityAddressToOffset(textureAddress, &tex->offset) == 0);
	
	// copy texture to video memory
	memcpy(textureAddress, png.bmp_out, size);

	// Setup tex struct
	tex->format = NV40_3D_TEX_FORMAT_FORMAT_A8R8G8B8 |
		      NV40_3D_TEX_FORMAT_LINEAR |
		      NV30_3D_TEX_FORMAT_DMA0 |
		      NV30_3D_TEX_FORMAT_NO_BORDER | 0x8000 |
		     (1 << NV40_3D_TEX_FORMAT_MIPMAP_COUNT__SHIFT);
	tex->wrap = NV30_3D_TEX_WRAP_S_REPEAT |
		    NV30_3D_TEX_WRAP_T_REPEAT |
		    NV30_3D_TEX_WRAP_R_REPEAT;
	tex->enable = NV40_3D_TEX_ENABLE_ENABLE;
	tex->filter = NV30_3D_TEX_FILTER_MIN_LINEAR |
	              NV30_3D_TEX_FILTER_MAG_LINEAR | 0x3fd6;
	tex->swizzle =
	    NV30_3D_TEX_SWIZZLE_S0_X_S1 | NV30_3D_TEX_SWIZZLE_S0_Y_S1 |
	    NV30_3D_TEX_SWIZZLE_S0_Z_S1 | NV30_3D_TEX_SWIZZLE_S0_W_S1 |
	    NV30_3D_TEX_SWIZZLE_S1_X_X | NV30_3D_TEX_SWIZZLE_S1_Y_Y |
	    NV30_3D_TEX_SWIZZLE_S1_Z_Z | NV30_3D_TEX_SWIZZLE_S1_W_W ;
	tex->width = png.width;
	tex->height = png.height;
	tex->stride = png.width * 4;

	free(png.bmp_out);

	return tex;
}
