#include <psl1ght/lv2.h>
#include <psl1ght/lv2/errno.h>

#include <errno.h>
#include <stdio.h>

// TODO: Actually convert the error codes
static s32 lv2Error(s32 error)
{
	return EINVAL;
}

s32 lv2Errno(s32 error)
{
	if (error >= 0)
		return error;
	errno = lv2Error(error);
	return -1;
}

s32 lv2ErrnoReentrant(struct _reent* r, s32 error)
{
	if (error >= 0)
		return error;
	r->_errno = lv2Error(error);
	return -1;
}
