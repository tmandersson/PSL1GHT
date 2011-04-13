#include <spu_intrinsics.h>

void spu_thread_exit(int status)
{
	spu_writech(SPU_WrOutMbox,result);
	si_stop(0x102);
}
