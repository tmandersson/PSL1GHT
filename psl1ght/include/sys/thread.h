#pragma once

#include <psl1ght/types.h>

EXTERN_BEGIN
#define THREAD_JOINABLE 1

typedef u64 sys_ppu_thread_t;
typedef struct sys_ppu_thread_stack_t_32 {
	u32 addr;
	u32 size;
}sys_ppu_thread_stack_t_32;

typedef struct sys_ppu_thread_stack_t {
	void* addr;
	u32 size;
}sys_ppu_thread_stack_t;

typedef struct sys_lwmutex_t {
	u32 owner;
	u32 waiter;
	u32 attribute;
	u32 recursive_count;
	u32 sleep_queue;
	u32 pad;
}sys_lwmutex_t;

#define LWMUTEX_ATTR_PROTOCOL  0x0002
#define LWMUTEX_ATTR_RECURSIVE 0x0010
typedef struct sys_lwmutex_attribute_t {
	u32 attr_protocol;
	u32 attr_recursive;
	char name[8];
}sys_lwmutex_attribute_t;

s32 sys_ppu_thread_create_ex(sys_ppu_thread_t * threadid, opd32* opdentry, u64 arg, s32 priority, u64 stacksize, u64 flags, char * threadname);

void sys_ppu_thread_yield();
s32 sys_ppu_thread_join(sys_ppu_thread_t threadid, u64 *retval);
s32 sys_ppu_thread_detach(sys_ppu_thread_t thread_id);
void sys_ppu_thread_get_join_state(s32 *isjoinable);
s32 sys_ppu_thread_set_priority(sys_ppu_thread_t threadid, s32  priority);
s32 sys_ppu_thread_get_priority(sys_ppu_thread_t threadid, s32* priority);
s32 sys_ppu_thread_get_stack_information(sys_ppu_thread_stack_t *stackinfo);
s32 sys_ppu_thread_rename(sys_ppu_thread_t id, char* name);
s32 sys_ppu_thread_recover_page_fault(sys_ppu_thread_t id);

EXTERN_END
