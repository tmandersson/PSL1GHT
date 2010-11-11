#pragma once

#include <psl1ght/types.h>

EXTERN_BEGIN

typedef enum
{
	SYSMODULE_NET=0,

	SYSMODULE_RTC=9,
	
	SYSMODULE_SYNC=0xd,
	SYSMODULE_FS,
	SYSMODULE_JPGDEC,
	SYSMODULE_GCM_SYS,
	SYSMODULE_AUDIO,
	
	SYSMODULE_NETCTL=0x14,
	SYSMODULE_SYSUTIL,
	SYSMODULE_SYSUTIL_NP,
	SYSMODULE_IO,
	SYSMODULE_PNGDEC,
	
	SYSMODULE_USBD = 0x1c
	
} id_module;

// create .opd 32 bits struct from 64 bits .opd addr
// the actual compilers uses 64 bits pointers but you need 32 bits pointers when one lib call to a remote function
// note it uses build_opd to alloc the fake .opd entry and return 32 bits addr from build_opd

inline uint32_t build32_func_addr(void *addr, uint64_t *build_opd) {
	
	uint64_t *addr_in=(uint64_t *) addr;

	*build_opd= (addr_in[0]<<32ULL) | addr_in[1];

	return (uint32_t) ((uint64_t) build_opd);
}

inline uint32_t get32_addr(void *addr) {
	
	return (uint32_t) (uint64_t) addr;
}


int SysLoadModule(id_module id);
int SysUnloadModule(id_module id);

EXTERN_END

