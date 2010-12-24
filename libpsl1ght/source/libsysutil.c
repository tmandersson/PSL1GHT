#include "sysutil/events.h"
#include "sysutil/msgdialog.h"

s32 sysRegisterCallback(sysEventSlot slot, sysCallback func, void * userdata)
{
	return sysRegisterCallback_ex(slot, OPD32(func), userdata);
}

s32 MsgDialogOpen(u32 type, const char * msg, MsgDialog func, void * userdata, void *unused)
{
	return MsgDialogOpen_ex(type, msg, OPD32(func), userdata, unused);
}

s32 MsgDialogErrorCode(u32 errorcode, MsgDialog func, void * userdata, void *unused)
{
    return MsgDialogErrorCode_ex(errorcode, OPD32(func), userdata, unused);
}
