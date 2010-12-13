#include <psl1ght/lv2/filesystem.h>
#include <psl1ght/lv2/tty.h>
#include <psl1ght/lv2/errno.h>

#include <sys/reent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <utime.h>

#include <sys/socket.h>

// TODO: Probably should be thread-safe by mapping these to threads?
#define UMASK(mode) ((mode) & ~glue_umask)
static mode_t glue_umask = 0;
mode_t umask(mode_t cmask)
{
	mode_t mode = glue_umask;
	glue_umask = cmask;
	return mode;
}

// Allows us to link in libnet on demand, and still use standard IO
#pragma weak closesocket
#pragma weak send
#pragma weak recv

#define DEFAULT_FILE_MODE UMASK(S_IRWXU | S_IRWXG | S_IRWXO)
int psl1ght_open_r(struct _reent* r, const char* path, int oflag, int mode)
{
	Lv2FsFile fd;

	oflag |= mode;

	int lv2flag = oflag & (O_ACCMODE | LV2_O_MSELF);
	if (oflag & O_CREAT)
		lv2flag |= LV2_O_CREAT;
	if (oflag & O_TRUNC)
		lv2flag |= LV2_O_TRUNC;
	if (oflag & O_EXCL)
		lv2flag |= LV2_O_EXCL;
	if (oflag & O_APPEND)
		lv2flag |= LV2_O_APPEND;

	mode = 0;
	if (oflag & O_WRONLY)
		mode = DEFAULT_FILE_MODE;

	int ret = lv2FsOpen(path, lv2flag, &fd, mode, NULL, 0);
	if (ret)
		return lv2ErrnoReentrant(r, ret);

	if (oflag & O_CREAT)
		lv2FsChmod(path, DEFAULT_FILE_MODE);

	return fd;
}

int _open64_r(struct _reent* r, const char* file, int flags, int mode)
{
	return psl1ght_open_r(r, file, flags, mode);
}

int psl1ght_fsync_r(struct _reent* r, int fd)
{
	return lv2ErrnoReentrant(r, lv2FsFsync(fd));
}

int _truncate_r(struct _reent* r, const char* path, off_t length)
{
	return lv2ErrnoReentrant(r, lv2FsTruncate(path, length));
}

int psl1ght_ftruncate_r(struct _reent* r, int fd, off_t length)
{
	return lv2ErrnoReentrant(r, lv2FsFtruncate(fd, length));
}

int closesocket(int fd);
int psl1ght_close_r(struct _reent* r, int fd)
{
	if (fd & SOCKET_FD_MASK)
		return closesocket(fd);

	return lv2ErrnoReentrant(r, lv2FsClose(fd));
}

int psl1ght_unlink_r(struct _reent* r, const char* path)
{
	return lv2ErrnoReentrant(r, lv2FsUnlink(path));
}

ssize_t psl1ght_write_r(struct _reent* r, int fd, const void* buffer, size_t size)
{
	if (fd & SOCKET_FD_MASK)
		return send(fd, buffer, size, 0);

	u64 written;
	int ret;
	if (fd == stdout->_file || fd == stderr->_file) {
		ret = lv2TtyWrite(fd, buffer, size, (u32*)(void*)&written);
		written >>= 32;
	} else
		ret = lv2FsWrite(fd, buffer, size, &written);

	if (ret)
		return lv2ErrnoReentrant(r, ret);
	return written;
}

ssize_t psl1ght_read_r(struct _reent* r, int fd, void* buffer, size_t size)
{
	if (fd & SOCKET_FD_MASK)
		return recv(fd, buffer, size, 0);

	u64 bytes;
	int ret;
	
	if (fd == stdin->_file) {
		ret = lv2TtyRead(fd, buffer, size, (u32*)(void*)&bytes);
		bytes >>= 32;
	} else
		ret = lv2FsRead(fd, buffer, size, &bytes);
	
	if (ret)
		return lv2ErrnoReentrant(r, ret);
	return bytes;
}

static void convertLv2Stat(struct stat* st, Lv2FsStat* stat)
{
	memset(st, 0, sizeof(struct stat));
	st->st_mode = stat->st_mode;
	st->st_uid = stat->st_uid;
	st->st_gid = stat->st_gid;
	st->st_atime = stat->st_atime;
	st->st_mtime = stat->st_mtime;
	st->st_ctime = stat->st_ctime;
	st->st_size = stat->st_size;
	st->st_blksize = stat->st_blksize;
}

int psl1ght_fstat_r(struct _reent* r, int fd, struct stat* buf)
{
	Lv2FsStat stat;
	int ret = lv2FsFstat(fd, &stat);
	if (!ret && buf)
		convertLv2Stat(buf, &stat);
	return lv2ErrnoReentrant(r, ret);
}

int _fstat64_r(struct _reent* r, int fd, struct stat* buf)
{
	return psl1ght_fstat_r(r, fd, buf);
}

int _stat_r(struct _reent* r, const char* path, struct stat* buf)
{
	Lv2FsStat stat;
	int ret = lv2FsStat(path, &stat);
	if (!ret && buf)
		convertLv2Stat(buf, &stat);
	return lv2ErrnoReentrant(r, ret);
}

int _mkdir_r(struct _reent* r, const char* path, mode_t mode)
{
	return lv2ErrnoReentrant(r, lv2FsMkdir(path, UMASK(mode)));
}

int _rmdir_r(struct _reent* r, const char* path)
{
	return lv2ErrnoReentrant(r, lv2FsRmdir(path));
}

int _rename_r(struct _reent* r, const char* old, const char* new)
{
	return lv2ErrnoReentrant(r, lv2FsRename(old, new));
}


int _link_r(struct _reent* r, const char* old, const char* new)
{
	r->_errno = ENOSYS;
	return -1;
}

off_t psl1ght_lseek_r(struct _reent* r, int fd, off_t offset, int whence)
{
	u64 position;
	int ret = lv2FsLSeek64(fd, offset, whence, &position);
	if (ret)
		return (off_t)lv2ErrnoReentrant(r, ret);
	return position;
}

off_t _lseek64_r(struct _reent* r, int fd, off_t offset, int whence)
{
	return psl1ght_lseek_r(r, fd, offset, whence);
}

int _utime_r(struct _reent* r, const char* path, const struct utimbuf* times)
{
	return lv2ErrnoReentrant(r, lv2FsUtime(path, (const Lv2FsUtimbuf*)times));
}

int isatty(int fd)
{
	if (fd == stdout->_file || fd == stdin->_file || fd == stderr->_file)
		return 1;
	errno = ENOTTY;
	return 0;
}

int psl1ght_chmod_r(struct _reent* r, const char* path, mode_t mode)
{
	return lv2ErrnoReentrant(r, lv2FsChmod(path, mode));
}
