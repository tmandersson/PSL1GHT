#include <psl1ght/lv2.h>

#include <sys/reent.h>
#include <sys/types.h>
#include <stddef.h>
#include <errno.h>

// 64kb page allocations
//#define PAGE_SIZE		0x10000
//#define PAGE_SIZE_FLAG	0x200

// 1mb page allocations
#define PAGE_SIZE		0x100000
#define PAGE_SIZE_FLAG	0x400

#define ROUND_UP(p, round) \
	((p + round - 1) & ~(round - 1))

// Here's a very lazy and lossy sbrk. It's made of fail, but I'm lazy.
char* memend = 0;
char* pageend = 0;
caddr_t psl1ght_sbrk_r(struct _reent* r, ptrdiff_t increment)
{
	if (increment == 0)
		return memend;
	if (increment < 0) // >.>
		return memend;
	if (memend + increment <= pageend) {
		void* ret = memend;
		memend += increment;
		return ret;
	}
	size_t allocsize = ROUND_UP(increment, PAGE_SIZE);
	u32 taddr;
	if (Lv2Syscall3(348, allocsize, PAGE_SIZE_FLAG, (u64)&taddr)) {
		r->_errno = ENOMEM;
		return (void*)-1;
	}
	char* addr = (char*)(u64)taddr;
	if (pageend != addr)
		memend = addr;
	pageend = addr + allocsize;
	char* ret = memend;
	memend += increment;
	return ret;
}
