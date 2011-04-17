/*! \file spu_event.h
  \brief SPU runtime library.

  These are the SPU library calls for SPU events.

  \see \ref spu_man
*/

#ifndef __SPU_EVENT_H__
#define __SPU_EVENT_H__

#include <stdint.h>
#include <sys/cdefs.h>

#define EVENT_DATA0_MASK		0x00FFFFFF
#define EVENT_PORT_SHIFT		24
#define EVENT_PORT_MAX_NUM		63

#ifdef __cplusplus
extern "C" {
#endif

/*! Send an SPU thread user event.

This function sends an SPU thread user event to an event queue.
The sent data will be received as \ref sys_event_t structure type. The data will be stored as the following:
- source = SPU_THREAD_EVENT_USER_KEY
- data_1 = SPU thread ID
- data_2 (upper 32 bits) = SPU port number
- data_2 (lower 32 bits) = lower 24 bits of <i>data0</i>
- data_3 = <i>data1</i>
\param spup SPU port number.
\param data0 Data 0 (only lower 24 bits are sent)
\param data1 Data 1
\return zero if no error occured, nonzero otherwise.
*/
int spu_thread_send_event(uint8_t spup,uint32_t data0,uint32_t data1);

int spu_thread_throw_event(uint8_t spup,uint32_t data0,uint32_t data1);

int spu_thread_receive_event(uint32_t spuq,uint32_t *data0,uint32_t *data1,uint32_t *data2);

int spu_thread_tryreceive_event(uint32_t spuq,uint32_t *data0,uint32_t *data1,uint32_t *data2);

#ifdef __cplusplus
	}
#endif

#endif
