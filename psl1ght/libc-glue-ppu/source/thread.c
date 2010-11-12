#include <psl1ght/lv2/thread.h>

#include <psl1ght/lv2/errno.h>

#include <stdio.h>
#include <errno.h>

s32 sys_ppu_thread_create(sys_ppu_thread_t * threadid, void (*entry) (u64 arg), u64 arg, s32 priority, u64 stacksize, u64 flags, char * threadname)
{
	/* This translates from the 64bit opd entry to the non standard 32bit opd entry */
	opd64 * opd = (opd64*)entry;
	opd32 newopd;
	newopd.func = (u64)opd->func;
	newopd.rtoc = (u64)opd->rtoc;
	return sys_ppu_thread_create_ex(threadid, &newopd, arg, priority, stacksize, flags, threadname);
}
void sys_ppu_thread_yield()
{
	lv2ThreadYield();
}

s32 sys_ppu_thread_join(sys_ppu_thread_t threadid, u64 *retval)
{
	return lv2ThreadJoin(threadid, retval);
}

s32 sys_ppu_thread_detach(sys_ppu_thread_t threadid)
{
	return lv2ThreadDetach(threadid);
}

void sys_ppu_thread_get_join_state(s32* isjoinable)
{
	lv2ThreadJoinState(isjoinable);
}

s32 sys_ppu_thread_set_priority(sys_ppu_thread_t threadid, s32  priority)
{
	return lv2ThreadSetPriority(threadid, priority);
}

s32 sys_ppu_thread_get_priority(sys_ppu_thread_t threadid, s32* priority)
{
	return lv2ThreadGetPriority(threadid, priority);
}

s32 sys_ppu_thread_get_stack_information(sys_ppu_thread_stack_t *stackinfo)
{
	sys_ppu_thread_stack_t_32 stackinfo32;
	s32 ret = lv2ThreadGetStackInformation(&stackinfo32);
	stackinfo->addr = (void*)(u64)stackinfo32.addr;
	stackinfo->size = stackinfo32.size;
	return ret;
}

s32 sys_ppu_thread_recover_page_fault(sys_ppu_thread_t id)
{
	return lv2ThreadRecoverPageFault(id);
}

s32 sys_ppu_thread_rename(sys_ppu_thread_t id, char* name)
{
	return lv2ThreadRename(id, name);
}

s32 sys_mutex_create(sys_mutex_t * mutexid, const sys_mutex_attribute_t *attr)
{
	return lv2MutexCreate(mutexid, attr);
}

s32 sys_mutex_destroy(sys_mutex_t mutexid)
{
	return lv2MutexDestroy(mutexid);
}

s32 sys_mutex_lock(sys_mutex_t mutexid, u64 timeout_usec)
{
	return lv2MutexLock(mutexid, timeout_usec);
}

s32 sys_mutex_trylock(sys_mutex_t mutexid)
{
	return lv2MutexTrylock(mutexid);
}

s32 sys_mutex_unlock(sys_mutex_t mutexid)
{
	return lv2MutexUnlock(mutexid);
}

s32 sys_cond_create(sys_cond_t * condid, sys_mutex_t mutexid, const sys_cond_attribute_t *attr)
{
	return lv2CondCreate(condid, mutexid, attr);
}

s32 sys_cond_destroy(sys_cond_t condid)
{
	return lv2CondDestroy(condid);
}

s32 sys_cond_wait(sys_cond_t condid, u64 timeout_usec)
{
	return lv2CondWait(condid, timeout_usec);
}

s32 sys_cond_signal(sys_cond_t condid)
{
	return lv2CondSignal(condid);
}

s32 sys_cond_signal_all(sys_cond_t condid)
{
	return lv2CondSignalAll(condid);
}

