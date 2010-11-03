#include <png.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "pngloader.h"

void ReadDataFromMemory(png_structp png_ptr, png_bytep outBytes, 
	png_size_t byteCountToRead);
void *seek; // Yeah, this isn't threadsafe, only load 1 png at a time.

void parseRGB(struct image *image, png_structp png_ptr,
	png_infop info_ptr) {
	
	png_uint_32 bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
	uint8_t *rowData = malloc(bytesPerRow);

	image->data = malloc(image->width * image->height * 4);
	uint32_t *data = image->data;

	// Read each row
	int row, col;
	for(row = 0; row < image->height; row++) {
		png_read_row(png_ptr, (png_bytep) rowData, NULL);

		int index = 0;
		for(col = 0; col < image->width; col++) {
			uint8_t red   = rowData[index++];
			uint8_t green = rowData[index++];
			uint8_t blue  = rowData[index++];
		
			*data = red << 16 | green << 8 | blue;
			data++;	
		}
	}

	free(rowData);
}

// Load a png from ram
// I can't be bothered handling errors correctly, lets just abort
struct image *loadPng(const uint8_t *png) {
	// Make sure we have a valid png here.
	assert(!png_check_sig((png_bytep) png, 8));
	
	// get PNG file info struct
	png_structp png_ptr = NULL;
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	assert(png_ptr != NULL);

	// get PNG image data info struct
	png_infop info_ptr = NULL;
	info_ptr = png_create_info_struct(png_ptr);
	assert(info_ptr != NULL);

	png_set_read_fn(png_ptr, (png_bytep) png, ReadDataFromMemory);

	// seek to start of png.
	seek = NULL;

	png_read_info(png_ptr, info_ptr);
	
	png_uint_32 width = 0;
	png_uint_32 height = 0;
	int bitDepth = 0;
	int colorType = -1;
	assert(png_get_IHDR(png_ptr, info_ptr,
		&width,
		&height,
		&bitDepth,
		&colorType,
		NULL, NULL, NULL) == 1);

	struct image *image= malloc(sizeof(struct image));
	image->width = width;
	image->height = height;
	
	switch(colorType) {
	case PNG_COLOR_TYPE_RGB:
		parseRGB(image, png_ptr, info_ptr);
		break;
	default:
		printf("Meh, I don't like this png\n");
		abort();
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	return image;
}

void ReadDataFromMemory(png_structp png_ptr, png_bytep outBytes, 
	png_size_t byteCountToRead) {
	if (seek == NULL) seek = png_get_io_ptr(png_ptr);
	
	memcpy(outBytes, seek, byteCountToRead);
	seek = seek + byteCountToRead;
}
