#pragma once

#include <psl1ght/types.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
#define MAX_PADS (127)
#define MAX_PORT_NUM (7)
typedef struct PadInfo
{
	u32 max;					/* max pads allowed to connect */
	u32 connected;				/* how many pads connected */
	u32 info;					/* bit 0 lets the system intercept pad? other bits are reserved */
	u16 vendor_id[MAX_PADS];	/* vendor id */
	u16 product_id[MAX_PADS];	/* product id */
	u8  status[MAX_PADS];		/* 0: Not connected, 1: Connected, 5: Connected to custom controller.*/
} PadInfo;

typedef struct PadInfo2
{
	u32 max;								/* max pads allowed to connect */
	u32 connected;							/* how many pads connected */
	u32 info;								/* Bit 0 lets the system intercept pad? other bits are reserved */
    u32 port_status[MAX_PORT_NUM];			/* Bit 0: Connected (0: Disconnected, 1: Connected), Bit 1: assign changes? */
    u32 port_setting[MAX_PORT_NUM];			/* Bit 1: Pressure sensitivity turned on, Bit 2: Sensors turned on */
    u32 device_capability[MAX_PORT_NUM];	/* See: PadCapabilityInfo. Bit 0: PS3SPEC, Bit 1: has_pressure, Bit 2: has_sensor, Bit 3: has_hps, Bit 4: has_vibrate */
    u32 device_type[MAX_PORT_NUM];			/* 0: Standard,  4: Bluray Remote, 5: LDD */ 
} PadInfo2;

#define PAD_MAX_CODES 64
typedef struct PadData
{
	s32 len;
	union{
		u16 button[PAD_MAX_CODES];
		struct {
			u16 zeroes;
			unsigned int				:  8; 		/* reserved */
			unsigned int seven 			:  4;		/* always 0x7 */
			unsigned int halflen 		:  4;		/* len/2 */
			unsigned int				:  8;		/* reserved */
			/* Button information */
			/* 0: UP, 1: DOWN     */
			unsigned int BTN_LEFT 		:  1;
			unsigned int BTN_DOWN 		:  1;
			unsigned int BTN_RIGHT 		:  1;
			unsigned int BTN_UP 		:  1;
			unsigned int BTN_START 		:  1;
			unsigned int BTN_R3 		:  1;
			unsigned int BTN_L3 		:  1;
			unsigned int BTN_SELECT		:  1;
			
			unsigned int				:  8;		/* reserved */
			unsigned int BTN_SQUARE 	:  1;
			unsigned int BTN_CROSS 		:  1;
			unsigned int BTN_CIRCLE 	:  1;
			unsigned int BTN_TRIANGLE	:  1;
			unsigned int BTN_R1 		:  1;
			unsigned int BTN_L1 		:  1;
			unsigned int BTN_R2 		:  1;
			unsigned int BTN_L2			:  1;
			
			/* Analog nub information */
			/* 0x0000 - 0x00FF        */
			unsigned int ANA_R_H		: 16;
			unsigned int ANA_R_V		: 16;
			unsigned int ANA_L_H		: 16;
			unsigned int ANA_L_V		: 16;
			
			/* Pressure-sensitive information */
			/* 0x0000 - 0x00FF                */
			unsigned int PRE_RIGHT		: 16;
			unsigned int PRE_LEFT		: 16;
			unsigned int PRE_UP			: 16;
			unsigned int PRE_DOWN		: 16;
			unsigned int PRE_TRIANGLE	: 16;
			unsigned int PRE_CIRCLE		: 16;
			unsigned int PRE_CROSS		: 16;
			unsigned int PRE_SQUARE		: 16;
			unsigned int PRE_L1			: 16;
			unsigned int PRE_R1			: 16;
			unsigned int PRE_L2			: 16;
			unsigned int PRE_R2			: 16;
			
			/* Sensor information */
			/* 0x0000 - 0x03FF    */
			unsigned int SENSOR_X		: 16;
			unsigned int SENSOR_Y		: 16;
			unsigned int SENSOR_Z		: 16;
			unsigned int SENSOR_G		: 16;
			u8 			 		reserved[80];		/* reserved */
		};
	};
} PadData;


#define PAD_CAPABILITY_INFO_MAX 32
typedef struct PadCapabilityInfo
{
	union {
		u32 info[PAD_CAPABILITY_INFO_MAX];
		struct {
			unsigned int ps3spec		:  1;		/* controller meets ps3 specifications */
			unsigned int has_pressure	:  1;		/* controller has pressure-sensitive buttons */
			unsigned int has_sensors	:  1;		/* controller has sensors, e.g. sixaxis, X,Y,Z,G */
			unsigned int has_hps		:  1;		/* controller has high precision stick */
			unsigned int has_vibrate	:  1;		/* controller has inbuilt vibration motor */
			unsigned int 				: 27;		/* reserved */
			u32 reserved[PAD_CAPABILITY_INFO_MAX-1];
		};
	};
} PadCapabilityInfo;

#define PAD_ACTUATOR_MAX	(2)
typedef struct PadActParam
{
	union {
		u8 motor[PAD_ACTUATOR_MAX];
		struct {
			/*  Small Motor  */
			/* 0: OFF, 1: On */
			u8 small_motor;
			/*  Large Motor                                  */
			/* 0: OFF, 1-255: Motor Speed, higher == faster. */
			u8 large_motor;
		};
	};
	u8 reserved[6];
} PadActParam;

typedef struct PadPeriphInfo
{
	u32 max;					/* max pads allowed to connect */
	u32 connected;				/* how many pads connected */
	u32 info;					/* bit 0 lets the system intercept pad? other bits are reserved */
    u32 port_status[MAX_PORT_NUM];			/* Bit 0: Connected (0: Disconnected, 1: Connected), Bit 1: assign changes? */
    u32 port_setting[MAX_PORT_NUM];			/* Bit 1: Pressure sensitivity turned on, Bit 2: Sensors turned on */
    u32 device_capability[MAX_PORT_NUM];	/* See: PadCapabilityInfo. Bit 0: PS3SPEC, Bit 1: has_pressure, Bit 2: has_sensor, Bit 3: has_hps, Bit 4: has_vibrate */
    u32 device_type[MAX_PORT_NUM];			/* 0: Standard,  4: Bluray Remote, 5: LDD */ 
    u32 pclass_type[MAX_PORT_NUM];
    u32 pclass_profile[MAX_PORT_NUM];
} PadPeriphInfo;

typedef struct PadPeriphData
{
  u32 pclass_type;
  u32 pclass_profile;
  s32 len;
  u16 button[PAD_MAX_CODES];
} PadPeriphData;


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
u32 ioPadSetActDirect(u32 port,	PadActParam*);
u32 ioPadLddDataInsert(s32 handle, PadData*);
s32 ioPadLddGetPortNo(s32 handle);
s32 ioPadLddRegisterController();
s32 ioPadLddUnregisterController(s32 handle);

/* new in 3.41 */
s32 ioPadGetInfo2(PadInfo2*);
s32 ioPadPeriphGetInfo(PadPeriphInfo*);
s32 ioPadPeriphGetData(u32 port, PadPeriphData*);
s32 ioPadSetPortSetting(u32 port, u32 setting);
#ifdef __cplusplus
}
#endif
