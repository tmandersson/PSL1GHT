/*! \file spu_event.h
  \brief SPU runtime library.

  These are the SPU library calls for SPU events.

  \see \ref spu_man
*/

#ifndef __SPU_EVENT_H__
#define __SPU_EVENT_H__

#include <stdint.h>
#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

int spu_thread_send_event(uint8_t spup,uint32_t data0,uint32_t data1);

int spu_thread_throw_event(uint8_t spup,uint32_t data0,uint32_t data1);

int spu_thread_receive_event(uint32_t spuq,uint32_t *data0,uint32_t *data1,uint32_t *data2);

int spu_thread_tryreceive_event(uint32_t spuq,uint32_t *data0,uint32_t *data1,uint32_t *data2);

#ifdef __cplusplus
	}
#endif

#endif
