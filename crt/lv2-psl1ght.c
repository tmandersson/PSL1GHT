#include <sys/syscalls.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

struct _reent libc_global_reent;

extern caddr_t psl1ght_sbrk_r(struct _reent* r, ptrdiff_t increment);
extern int psl1ght_close_r(struct _reent* r, int fd);
extern int psl1ght_open_r(struct _reent* r, const char* path, int oflag, int mode);
extern ssize_t psl1ght_read_r(struct _reent* r, int fd, void* buffer, size_t size);
extern ssize_t psl1ght_write_r(struct _reent* r, int fd, const void* buffer, size_t size);
extern off_t psl1ght_lseek_r(struct _reent* r, int fd, off_t offset, int whence);
extern int psl1ght_fstat_r(struct _reent* r, int fd, struct stat* buf);
extern int psl1ght_ftruncate_r(struct _reent* r, int fd, off_t length);
extern int psl1ght_fsync_r(struct _reent* r, int fd);
extern int psl1ght_unlink_r(struct _reent* r, const char* path);
extern int psl1ght_chmod_r(struct _reent* r, const char* path, mode_t mode);

__attribute__((constructor(104)))
static void initSyscalls()
{
	__syscalls.sbrk_r = psl1ght_sbrk_r;
	__syscalls.close_r = psl1ght_close_r;
	__syscalls.open_r = psl1ght_open_r;
	__syscalls.read_r = psl1ght_read_r;
	__syscalls.write_r = psl1ght_write_r;
	__syscalls.lseek_r = psl1ght_lseek_r;
	__syscalls.fstat_r = psl1ght_fstat_r;
	__syscalls.ftruncate_r = psl1ght_ftruncate_r;
	__syscalls.fsync_r = psl1ght_fsync_r;
	__syscalls.unlink_r = psl1ght_unlink_r;
	__syscalls.chmod_r = psl1ght_chmod_r;
}
