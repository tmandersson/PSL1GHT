#include <stdint.h>
#include <spu_intrinsics.h>

int spu_thread_send_event(uint8_t spup,uint32_t data0,uint32_t data1)
{
	vec_char16 v = si_selb(si_from_uint(spup<<24),si_from_uint(data0),si_fsmbi(0x7777));

	if(spup>63) return 0x80010002;
	if(spu_readchcnt(SPU_RdInMbox)>0) return 0x8001000A;

	spu_writech(SPU_WrOutMbox,data1);
	spu_writechqw(SPU_WrOutIntrMbox,v);

	return (int)spu_readch(SPU_RdInMbox);
}
