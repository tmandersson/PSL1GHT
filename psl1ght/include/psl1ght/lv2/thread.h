#pragma once

#include <psl1ght/lv2.h>

#include <sys/thread.h>

s32 sys_ppu_thread_create(sys_ppu_thread_t * threadid, void (*entry) (u64 arg), u64 arg, s32 priority, u64 stacksize, u64 flags, char * threadname);
s32 sys_ppu_thread_get_id(sys_ppu_thread_t * threadid);
void sys_ppu_thread_exit(u64 val);
s32 sys_lwmutex_create(sys_lwmutex_t *lwmutex, const sys_lwmutex_attribute_t *lwmutex_attr);
void sys_lwmutex_destroy(sys_lwmutex_t *lwmutex);
s32 sys_lwmutex_lock(sys_lwmutex_t *lwmutex);
void sys_lwmutex_unlock(sys_lwmutex_t *lwmutex);

LV2_SYSCALL lv2ThreadYield() { return Lv2Syscall0(43); }
LV2_SYSCALL lv2ThreadJoin(sys_ppu_thread_t threadid, u64 *retval) { return Lv2Syscall2(44, threadid, (u64)retval); }
LV2_SYSCALL lv2ThreadDetach(sys_ppu_thread_t threadid) { return Lv2Syscall1(45, threadid); }
LV2_SYSCALL lv2ThreadJoinState(s32* isjoinable) { return Lv2Syscall1(46, (u64)isjoinable); }
LV2_SYSCALL lv2ThreadSetPriority(sys_ppu_thread_t threadid, s32 priority) { return Lv2Syscall2(47, threadid, priority); }
LV2_SYSCALL lv2ThreadGetPriority(sys_ppu_thread_t threadid, s32* priority) { return Lv2Syscall2(48, threadid, (u64)priority); }
LV2_SYSCALL lv2ThreadGetStackInformation(sys_ppu_thread_stack_t_32 *stackinfo) { return Lv2Syscall1(49, (u64)stackinfo); }
LV2_SYSCALL lv2ThreadRename(sys_ppu_thread_t id, char*name) { return Lv2Syscall2(56, id, (u64)name); }
LV2_SYSCALL lv2ThreadRecoverPageFault(sys_ppu_thread_t threadid) { return Lv2Syscall1(57, threadid); }
