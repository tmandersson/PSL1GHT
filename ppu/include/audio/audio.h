/*! \file audio.h
\brief Audio library.
*/

#ifndef __LV2_AUDIO_H__
#define __LV2_AUDIO_H__

#include <sys/event_queue.h>

#define AUDIO_BLOCK_SAMPLES				256

#define AUDIO_STATUS_READY				1
#define AUDIO_STATUS_RUN				2
#define AUDIO_STATUS_CLOSE				0x1010

/*! \brief 2-channel (stereo) output. */
#define AUDIO_PORT_2CH					2
/*! \brief 8-channel output. */
#define AUDIO_PORT_8CH					8

#define AUDIO_PORT_INITLEVEL			0x1000

#define AUDIO_BLOCK_8					8
#define AUDIO_BLOCK_16					16
#define AUDIO_BLOCK_32					32

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Audio port parameter data structure. */
typedef struct _audio_port_param
{
	/*! \brief Number of channels.

	Possible values are:
	- \ref AUDIO_PORT_2CH
	- \ref AUDIO_PORT_8CH
	*/
	u64 numChannels;
	/*! \brief Number of blocks in audio buffer.

	Possible values are:
	- \ref AUDIO_BLOCK_8
	- \ref AUDIO_BLOCK_16
	- \ref AUDIO_BLOCK_32
	*/
	u64 numBlocks;

	/*! \brief Special attributes.

	This value must be either 0 or \ref AUDIO_PORT_INITLEVEL.
	*/
	u64 attrib;
	f32 level;
} audioPortParam;

typedef struct _audio_port_config
{
	u32 readIndex;
	u32 status;
	u64 channelCount;
	u64 numBlocks;
	u32 portSize;
	u32 audioDataStart;
} audioPortConfig;

/*! \brief Initialize audio subsystem.
\return zero if no error, nonzero otherwise.
*/
s32 audioInit();

/*! \brief Initialize audio subsystem.
\return zero if no error, nonzero otherwise.
*/
s32 audioQuit();


s32 audioPortOpen(audioPortParam *param,u32 *portNum);
s32 audioPortStart(u32 portNum);
s32 audioPortStop(u32 portNum);
s32 audioGetPortConfig(u32 portNum,audioPortConfig *config);
s32 audioPortClose(u32 portNum);
s32 audioCreateNotifyEventQueue(sys_event_queue_t *eventQ,u64 *queueKey);
s32 audioSetNotifyEventQueue(u64 queueKey);
s32 audioRemoveNotifyEventQueue(u64 queueKey);

#ifdef __cplusplus
	}
#endif

#endif
