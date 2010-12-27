#include <psl1ght/lv2.h>
#include <psl1ght/lv2/errno.h>

#include <errno.h>
#include <stdio.h>

#include <sys/errno.h>

s32 lv2Errno(s32 error)
{
	if (error >= 0)
		return error;

	switch( error)
	{
    case 0x80010009:/* Not super-user */ 
         errno = EPERM; /* 1 */ 
         break;
    case 0x80010006:/* No such file or directory */ 
         errno = ENOENT; /* 2 */ 
         break;
    case 0x80010005:/* No such process */ 
         errno = ESRCH; /* 3 */ 
         break;
    case 0x8001001F:/* Interrupted system call */ 
         errno = EINTR; /* 4 */ 
         break;
    case 0x8001002B:/* I/O error */ 
         errno = EIO; /* 5 */ 
         break;
    case 0x8001002F:/* No such device or address */ 
         errno = ENXIO; /* 6 */ 
         break;
    case 0x80010007:/* Exec format error */ 
         errno = ENOEXEC; /* 8 */ 
         break;
    case 0x8001002A:/* Bad file number */ 
         errno = EBADF; /* 9 */ 
         break;
    case 0x80010001:/* No more processes */ 
         errno = EAGAIN; /* 11 */ 
         break;
    case 0x80010004:/* Not enough core */ 
         errno = ENOMEM; /* 12 */ 
         break;
    case 0x80010029:/* Permission denied */ 
         errno = EACCES; /* 13 */ 
         break;
    case 0x8001000D:/* Bad address */ 
         errno = EFAULT; /* 14 */ 
         break;
    case 0x8001000A:/* Mount device busy */ 
         errno = EBUSY; /* 16 */ 
         break;
    case 0x80010014:/* File exists */ 
         errno = EEXIST; /* 17 */ 
         break;
    case 0x80010030:/* Cross-device link */ 
         errno = EXDEV; /* 18 */ 
         break;
    case 0x8001002D:/* No such device */ 
         errno = ENODEV; /* 19 */ 
         break;
    case 0x8001002E:/* Not a directory */ 
         errno = ENOTDIR; /* 20 */ 
         break;
    case 0x80010012:/* Is a directory */ 
         errno = EISDIR; /* 21 */ 
         break;
    case 0x80010002:/* Invalid argument */ 
         errno = EINVAL; /* 22 */ 
         break;
    case 0x80010022:/* Too many open files in system */ 
         errno = ENFILE; /* 23 */ 
         break;
    case 0x8001002C:/* Too many open files */ 
         errno = EMFILE; /* 24 */ 
         break;
    case 0x80010024:/* Not a typewriter */ 
         errno = ENOTTY; /* 25 */ 
         break;
    case 0x80010020:/* File too large */ 
         errno = EFBIG; /* 27 */ 
         break;
    case 0x80010023:/* No space left on device */ 
         errno = ENOSPC; /* 28 */ 
         break;
    case 0x80010027:/* Illegal seek */ 
         errno = ESPIPE; /* 29 */ 
         break;
    case 0x80010026:/* Read only file system */ 
         errno = EROFS; /* 30 */ 
         break;
    case 0x80010021:/* Too many links */ 
         errno = EMLINK; /* 31 */ 
         break;
    case 0x80010025:/* Broken pipe */ 
         errno = EPIPE; /* 32 */ 
         break;
    case 0x8001001B:/* Math arg out of domain of func */ 
         errno = EDOM; /* 33 */ 
         break;
    case 0x8001001C:/* Math result not representable */ 
         errno = ERANGE; /* 34 */ 
         break;
    case 0x80010008:/* Deadlock condition */ 
         errno = EDEADLK; /* 45 */ 
         break;
    case 0x80010035:/* No record locks available */ 
         errno = ENOLCK; /* 46 */ 
         break;
    case 0x80010031:/* Trying to read unreadable message */ 
         errno = EBADMSG; /* 77 */ 
         break;
    case 0x80010003:/* Function not implemented */ 
         errno = ENOSYS; /* 88 */ 
         break;
    case 0x80010036:/* Directory not empty */ 
         errno = ENOTEMPTY; /* 90 */ 
         break;
    case 0x80010034:/* File or path name too long */ 
         errno = ENAMETOOLONG; /* 91 */ 
         break;
    case 0x8001000B:/* Connection timed out */ 
         errno = ETIMEDOUT; /* 116 */ 
         break;
    case 0x80010032:/* Connection already in progress */ 
         errno = EINPROGRESS; /* 119 */ 
         break;
    case 0x80010033:/* Message too long */ 
         errno = EMSGSIZE; /* 122 */ 
         break;
    case 0x80010015:/* Socket is already connected */ 
         errno = EISCONN; /* 127 */ 
         break;
    case 0x80010016:/* Socket is not connected */ 
         errno = ENOTCONN; /* 128 */ 
         break;
    case 0x80010037:/* Not supported */ 
         errno = ENOTSUP; /* 134 */ 
         break;
    case 0x8001001D:
         errno = EILSEQ; /* 138 */ 
         break;
    case 0x80010039:/* Value too large for defined data type */ 
         errno = EOVERFLOW; /* 139 */ 
         break;
    case 0x80010013:/* Operation canceled */ 
         errno = ECANCELED; /* 140 */ 
         break;

	default:
		errno = EINVAL; // TODO: Actually convert the error codes
		break;
	}
	return errno;
}
