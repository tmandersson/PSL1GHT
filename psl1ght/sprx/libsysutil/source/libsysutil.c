#include "sysutil/events.h"

s32 sysRegisterCallback(sysEventSlot slot, sysCallback func, void * userdata)
{
	opd64 * opd = (opd64*)func;
	opd32 newopd;
	newopd.func = (u64)opd->func;
	newopd.rtoc = (u64)opd->rtoc;
	
	return sysRegisterCallback_ex(slot, &newopd, userdata);
}

