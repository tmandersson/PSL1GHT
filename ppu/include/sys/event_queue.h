/*! \file event_queue.h
 \brief Event queue management functions.
*/

#ifndef __SYS_EVENT_QUEUE_H__
#define __SYS_EVENT_QUEUE_H__

#include <ppu-lv2.h>

#ifdef __cplusplus
	extern "C" {
#endif

/*! \brief Event queue id */
typedef u32 sys_event_queue_t;

/*! \brief Data structure for received event data. */
typedef struct sys_event
{
	u64 source;			/*!< \brief id of emitting source */
	u64 data_1;			/*!< \brief data field 1 */
	u64 data_2;			/*!< \brief data field 2 */
	u64 data_3;			/*!< \brief data field 3 */
} sys_event_t;

/*! \brief Destroy an event queue.
\param eventQ The event queue id.
\param mode Destroy mode (0: normal).
\return zero if no error, nonzero otherwise.
*/
LV2_SYSCALL sysEventQueueDestroy(sys_event_queue_t eventQ,s32 mode)
{
	return lv2syscall2(129,eventQ,mode);
}

/*! \brief Receive an event from an event queue.

The current thread blocks until an event is received or the timeout period
(in microseconds) has been reached.
\param eventQ The event queue id.
\param event Pointer to a structure for received event data.
\param timeout_usec Timeout period, or 0 for no timeout.
\return zero if an event was received, nonzero if the timeout delay was reached
        or if an error occured.
*/
LV2_SYSCALL sysEventQueueReceive(sys_event_queue_t eventQ,sys_event_t *event,u64 timeout_usec)
{
	return lv2syscall3(130,eventQ,(u64)event,timeout_usec);
}

/*! \brief Drain an event queue.

This function removes all pending events in the queue, making it empty.
\param eventQ The event queue id.
\return zero if no error, nonzero otherwise.
*/
LV2_SYSCALL sysEventQueueDrain(sys_event_queue_t eventQ)
{
	return lv2syscall1(133,eventQ);
}

#ifdef __cplusplus
	}
#endif

#endif
