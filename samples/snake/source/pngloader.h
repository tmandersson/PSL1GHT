#pragma once

#include <psl1ght/types.h>

struct image {
	int width;
	int height;
	uint32_t *data;
};

struct image *loadPng(const uint8_t *png);


