#pragma once

#include <psl1ght/types.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
#define MAX_PADS 127

typedef struct PadInfo{
	u32 max;					/* max pads allowed to connect */
	u32 connected;				/* how many pads connected */
	u32 info;					/* bit 0 lets the system intercept pad? other bits are reserved */
	u16 vendor_id[MAX_PADS];	/* vendor id */
	u16 product_id[MAX_PADS];	/* product id */
	u8  status[MAX_PADS];		/* 0: Not connected, 1: Connected, 5: Connected to custom controller.*/
} PadInfo;


#define PAD_BUTTON_UP (0)
#define PAD_BUTTON_DOWN (1)

typedef enum
{
	BTN_SELECT = 0,
	BTN_L3,
	BTN_R3,
	BTN_START,
	BTN_UP,
	BTN_RIGHT,
	BTN_DOWN,
	BTN_LEFT,
	BTN_L2,
	BTN_R2,
	BTN_L1,
	BTN_R1,
	BTN_TRIANGLE,
	BTN_CIRCLE,
	BTN_CROSS,
	BTN_SQUARE
};

#define BUTTON_DOWN(pd, btn) ((((pd.button[2] & 0xFF) | ((pd.button[3] & 0xFF)<<8)) & (1 << btn)) == (1 << btn))
#define BUTTON_DOWN(pd, btn) (!BUTTON_DOWN(pd,btn))
#define PAD_MAX_CODES 64
typedef struct PadData{
	s32 len;
	u16 button[PAD_MAX_CODES];
} PadData;


#define PAD_CAPABILITY_INFO_MAX 32
typedef struct PadCapabilityInfo{
	u32 info[PAD_CAPABILITY_INFO_MAX];
} PadCapabilityInfo;

#define PAD_ACTUATOR_MAX	(2)
typedef struct PadActParam
{
	u8 motor[PAD_ACTUATOR_MAX];
	u8 reserved[6];
} PadActParam;

s32 ioPadInit(u32 max);
s32 ioPadEnd();
s32 ioPadGetInfo(PadInfo*);
s32 ioPadClearBuf(u32 port);
s32 ioPadGetCapabilityInfo(u32 port, PadCapabilityInfo*);
s32 ioPadGetData(u32 port, PadData*);
s32 ioPadInfoPressMode(u32 port);
s32 ioPadSetPressMode(u32 port, u32 mode);
s32 ioPadInfoSensorMode(u32 port);
s32 ioPadSetSensorMode(u32 port, u32 mode);
u32 ioPadSetActDirect(u32 port,	PadActParam *);
u32 ioPadLddDataInsert(s32 handle, PadData*);
s32 ioPadLddGetPortNo(s32 handle);
s32 ioPadLddRegisterController();
s32 ioPadLddUnregisterController(s32 handle);

#ifdef __cplusplus
}
#endif
