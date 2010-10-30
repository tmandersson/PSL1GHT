#include <unistd.h>

#include <lv2/process.h>

void _fini();

void _exit(int status)
{
	_fini();
	sysProcessExit(status);
}
