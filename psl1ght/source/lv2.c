#include <psl1ght/lv2.h>
#include <psl1ght/lv2/errno.h>

#include <errno.h>

s32 lv2Errno(s32 error)
{
	if (error >= 0)
		return error;
	printf("Error found: %d\n", error);
	errno = EINVAL; // TODO: Actually convert the error codes
	return -1;
}
