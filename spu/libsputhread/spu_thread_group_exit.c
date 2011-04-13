#include <spu_intrinsics.h>

void spu_thread_group_exit(int result)
{
	spu_writech(SPU_WrOutMbox,result);
	si_stop(0x101);
}
