#include "config.h"

typedef struct {
	int unk1;
	int unk2;
	int zero1;
	int zero2;
	const char* name;
	const void* fnid;
	const void* fstub;
	int zero5;
	int zero6;
	int zero7;
	int zero8;
} prx_header;

extern unsigned int LIBRARY_SYMBOL __attribute__((section(".rodata.sceFNID")));
static const void* scefstub[0] __attribute__((section(".data.sceFStub." LIBRARY_NAME)));

static const int version __attribute__((section(".rodata.sceResident"))) = 0;
static const const char name[] __attribute__((section(".rodata.sceResident"))) = LIBRARY_NAME;

prx_header header __attribute__((section(".lib.stub"))) = {
	LIBRARY_HEADER_1,
	LIBRARY_HEADER_2,
	0,
	0,
	name,
	&LIBRARY_SYMBOL,
	scefstub,
	0,
	0,
	0,
	0
};

#define EXPORT(name, fnid) \
	extern void* __##name; \
	const void* name##_stub __attribute__((section(".data.sceFStub." LIBRARY_NAME))) = &__##name; \
	const unsigned int name##_fnid __attribute__((section(".rodata.sceFNID"))) = fnid;

#include "exports.c"
