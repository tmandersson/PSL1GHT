#include <stdint.h>
#include <spu_intrinsics.h>

int spu_thread_throw_event(uint8_t spup,uint32_t data0,uint32_t data1)
{
	vec_char16 v = si_selb(si_from_uint(0x40000000),si_from_uint(data0),si_fsmbi(0x7777));

	if(spup>63) return 0x80010002;

	spu_writech(SPU_WrOutMbox,data1);
	spu_writechqw(SPU_WrOutIntrMbox,(v | si_from_uint(spup<<24)));

	return 0;
}
