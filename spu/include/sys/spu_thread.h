/*! \file spu_thread.h
  \brief SPU runtime library.

  These are the SPU library calls for SPU threads.

  \see \ref spu_man
*/

#ifndef __SPU_THREAD_H__
#define __SPU_THREAD_H__

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Terminate the running SPU thread group.
 \param status
 The thread group's returned exit status value.
*/
void spu_thread_group_exit(int status);

/*! \brief Preempt the running SPU thread group.

*/
void spu_thread_group_yield(void);
	
/*! \brief Terminate the running SPU thread.
 \param status
 The thread's returned exit status value.
*/
void spu_thread_exit(int status);

#ifdef __cplusplus
	}
#endif

#endif
