#include <stdlib.h>
#include <sys/reent.h>

struct _reent libc_global_reent;

int main(int argc, const char* argv[], const char* envp[]);

extern void _init();

static const char* envp[] = { 0 };
const char** environ = envp;

void _initialize(int argc, const char* argv[])
{
	_init();
	int ret = main(argc, argv, envp);
	exit(ret);
}
