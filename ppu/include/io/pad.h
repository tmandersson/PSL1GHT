/*! \file pad.h
\brief PS3 pad/controller management.
*/

#ifndef __LV2_PAD_H__
#define __LV2_PAD_H__

#include <ppu-types.h>

#define MAX_PADS					(127)
#define MAX_PAD_CODES				(64)
#define MAX_PORT_NUM				(7)
#define MAX_PAD_CAPABILITY_INFO		(32)
#define MAX_PAD_ACTUATOR			(2)

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Pad info data structure (old format). */
typedef struct _pad_info
{
	u32 max;					/*!< \brief max pads allowed to connect */
	u32 connected;				/*!< \brief how many pads connected */
	u32 info;					/*!< \brief bit 0 lets the system intercept pad? other bits are reserved */
	u16 vendor_id[MAX_PADS];	/*!< \brief array of vendor ids */
	u16 product_id[MAX_PADS];	/*!< \brief array of product ids */
	u8 status[MAX_PADS];		/*!< \brief array of pad statuses */
} padInfo;

/*! \brief Pad info data structure (new format). */
typedef struct _pad_info2
{
	u32 max;						/*!< \brief max pads allowed to connect */
	u32 connected;					/*!< \brief how many pads connected */
	u32 info;						/*!< \brief Bit 0 lets the system intercept pad? other bits are reserved */
    u32 port_status[MAX_PORT_NUM];	/*!< \brief Bit 0: Connected (0: Disconnected, 1: Connected), Bit 1: assign changes? */
    u32 port_setting[MAX_PORT_NUM]; /*!< \brief Bit 1: Pressure sensitivity turned on, Bit 2: Sensors turned on */
    u32 device_capability[MAX_PORT_NUM]; /*!< \brief See: PadCapabilityInfo. Bit 0: PS3SPEC, Bit 1: has_pressure, Bit 2: has_sensor, Bit 3: has_hps, Bit 4: has_vibrate */
    u32 device_type[MAX_PORT_NUM];	/*!< \brief 0: Standard, 4: Bluray Remote, 5: LDD */
} padInfo2;

/*! \brief Pad data data structure.

All 1-bit button fields are zero when inctive, and 1 when active.
*/
typedef struct _pad_data
{
	s32 len;						/*!< \brief structure length */
	union{
		u16 button[MAX_PAD_CODES];	/*!< \brief array of button values */
		struct {
			u16 zeroes;				/*!< \brief zero bits */
			unsigned int : 8; 		/*!< \brief reserved */
			unsigned int seven : 4;	/*!< \brief always 0x7 */
			unsigned int halflen : 4; /*!< \brief len/2 */
			unsigned int : 8;		/*!< \brief reserved */
			/* Button information */
			/* 0: UP, 1: DOWN */
			unsigned int BTN_LEFT : 1;		/*!< \brief left button */
			unsigned int BTN_DOWN : 1;		/*!< \brief down button */
			unsigned int BTN_RIGHT : 1;		/*!< \brief right button */
			unsigned int BTN_UP : 1;		/*!< \brief up button */
			unsigned int BTN_START : 1;		/*!< \brief start button */
			unsigned int BTN_R3 : 1;		/*!< \brief R3 button */
			unsigned int BTN_L3 : 1;		/*!< \brief L3 button */
			unsigned int BTN_SELECT : 1;	/*!< \brief select button */

			unsigned int : 8;				/*!< \brief reserved */
			unsigned int BTN_SQUARE : 1;	/*!< \brief square button */
			unsigned int BTN_CROSS : 1;		/*!< \brief cross button */
			unsigned int BTN_CIRCLE : 1;	/*!< \brief circle button */
			unsigned int BTN_TRIANGLE : 1;	/*!< \brief triangle button */
			unsigned int BTN_R1 : 1;		/*!< \brief R1 button */
			unsigned int BTN_L1 : 1;		/*!< \brief L1 button */
			unsigned int BTN_R2 : 1;		/*!< \brief R2 button */
			unsigned int BTN_L2 : 1;		/*!< \brief L2 button */

			/* Analog nub information */
			/* 0x0000 - 0x00FF */
			/*! \brief right analog nub horizontal position (\c 0x0000 - \c 0x00FF) */
			unsigned int ANA_R_H : 16;
			/*! \brief right analog nub vertical position (\c 0x0000 - \c 0x00FF) */
			unsigned int ANA_R_V : 16;
			/*! \brief left analog nub horizontal position (\c 0x0000 - \c 0x00FF) */
			unsigned int ANA_L_H : 16;
			/*! \brief left analog nub vertical position (\c 0x0000 - \c 0x00FF) */
			unsigned int ANA_L_V : 16;

			/* Pressure-sensitive information */
			/* 0x0000 - 0x00FF */
			/*! \brief right button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_RIGHT : 16;
			/*! \brief left button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_LEFT : 16;
			/*! \brief up button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_UP : 16;
			/*! \brief down button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_DOWN : 16;
			/*! \brief triangle button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_TRIANGLE : 16;
			/*! \brief circle button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_CIRCLE : 16;
			/*! \brief cross button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_CROSS : 16;
			/*! \brief square button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_SQUARE : 16;
			/*! \brief L1 button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_L1 : 16;
			/*! \brief R1 button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_R1 : 16;
			/*! \brief L2 button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_L2 : 16;
			/*! \brief R2 button pressure information (\c 0x0000 - \c 0x00FF) */
			unsigned int PRE_R2 : 16;

			/* Sensor information */
			/* 0x0000 - 0x03FF */
			/*! \brief X sensor information (\c 0x0000 - \c 0x03FF) */
			unsigned int SENSOR_X : 16;
			/*! \brief Y sensor information (\c 0x0000 - \c 0x03FF) */
			unsigned int SENSOR_Y : 16;
			/*! \brief Z sensor information (\c 0x0000 - \c 0x03FF) */
			unsigned int SENSOR_Z : 16;
			/*! \brief G sensor information (\c 0x0000 - \c 0x03FF) */
			unsigned int SENSOR_G : 16;
			/*! \brief reserved */
			u8 reserved[80];
		};
	};
} padData;

/*! \brief Pad capability information data structure.

All 1-bit values are 1 when the capability is present, 0 otherwise.
*/
typedef struct _pad_capability_info
{
	union {
		/*! \brief The whole capabilities in an array of 32-bit integers. */
		u32 info[MAX_PAD_CAPABILITY_INFO];
		struct {
			unsigned int ps3spec : 1;		/*!< \brief controller meets ps3 specifications */
			unsigned int has_pressure : 1;	/*!< \brief controller has pressure-sensitive buttons */
			unsigned int has_sensors : 1;	/*!< \brief controller has sensors, e.g. sixaxis, X,Y,Z,G */
			unsigned int has_hps : 1;		/*!< \brief controller has high precision stick */
			unsigned int has_vibrate : 1;	/*!< \brief controller has inbuilt vibration motor */
			unsigned int : 27;				/*!< \brief reserved */
			u32 reserved[MAX_PAD_CAPABILITY_INFO-1];	/*!< \brief reserved */
		};
	};
} padCapabilityInfo;

/*! \brief Pad action parameters data structure. */
typedef struct _pad_act_param
{
	union {
		/*! \brief All motors statuses. */
		u8 motor[MAX_PAD_ACTUATOR];
		struct {
			/*! \brief Small Motor parameter 0: OFF, 1: On */
			u8 small_motor;
			/*! \brief Large Motor 0: OFF, 1-255: Motor Speed, higher == faster. */
			u8 large_motor;
		};
	};
	/*! \brief reserved */
	u8 reserved[6];
} padActParam;

/*! \brief Pad peripheral information data structure. */
typedef struct _pad_periph_info
{
	u32 max; /*!< \brief max pads allowed to connect */
	u32 connected; /*!< \brief how many pads connected */
	u32 info; /*!< \brief bit 0 lets the system intercept pad? other bits are reserved */
    u32 port_status[MAX_PORT_NUM]; /*!< \brief Bit 0: Connected (0: Disconnected, 1: Connected), Bit 1: assign changes? */
    u32 port_setting[MAX_PORT_NUM]; /*!< \brief Bit 1: Pressure sensitivity turned on, Bit 2: Sensors turned on */
	/*! \brief Pad capability.
	
	- Bit 0: PS3SPEC
	- Bit 1: has_pressure
	- Bit 2: has_sensor
	- Bit 3: has_hps
	- Bit 4: has_vibrate
	\see \ref padCapabilityInfo
	*/
    u32 device_capability[MAX_PORT_NUM];
    u32 device_type[MAX_PORT_NUM]; /*!< \brief 0: Standard, 4: Bluray Remote, 5: LDD */
    u32 pclass_type[MAX_PORT_NUM]; /*!< \brief Pad class type */
    u32 pclass_profile[MAX_PORT_NUM]; /*!< \brief Pad class profile */
} padPeriphInfo;

/*! \brief Pad peripheral data data structure. */
typedef struct _pad_periph_data
{
	u32 pclass_type;			/*!< \brief Pad class type */
	u32 pclass_profile;			/*!< \brief Pas class profile */
	s32 len;					/*!< \brief Length of button array */
	u16 button[MAX_PAD_CODES];	/*!< \brief Button array */
} padPeriphData;

/*! \brief Initialize Pad IO management.
\param max maximum number of supported pads.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadInit(u32 max);

/*! \brief End of Pad IO management.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadEnd();

/*! \brief Get pad information.
\param info Pointer to the pad info structure.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadGetInfo(padInfo* info);

/*! \brief Clear pad buffer.
\param port Pad port.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadClearBuf(u32 port);

/*! \brief Get pad capability information.
\param port Pad port.
\param capabilities Pointer to the pad capability information structure.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadGetCapabilityInfo(u32 port, padCapabilityInfo* capabilities);

/*! \brief Get pad data.
\param port Pad port.
\param capabilities Pointer to the pad data structure.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadGetData(u32 port, padData* data);

/*! \brief Get pad press mode.
\param port Pad port.
\return The current press mode value, or a negative value in case of error.
*/
s32 ioPadInfoPressMode(u32 port);

/*! \brief Set pad press mode.
\param port Pad port.
\param mode The selected press mode.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadSetPressMode(u32 port, u32 mode);

/*! \brief Get pad sensor mode.
\param port Pad port.
\return The current sensor mode value, or a negative value in case of error.
*/
s32 ioPadInfoSensorMode(u32 port);

/*! \brief Set pad sensor mode.
\param port Pad port.
\param mode The selected sensor mode.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadSetSensorMode(u32 port, u32 mode);

/*! \brief Set pad action (rumble) data.
\param port Pad port.
\param actParam Pointer to the action data structure.
\return zero if no error occured, nonzero otherwise.
*/
u32 ioPadSetActDirect(u32 port, padActParam* actParam);

/*! \brief Insert pad data into virtual pad.
\param handle The registered handle for the virtual pad.
\param padData Pointer to the pad data value.
\return zero if no error occured, nonzero otherwise.
\todo to be confirmed.
*/
u32 ioPadLddDataInsert(s32 handle, padData* data);

/*! \brief Get port number from registered virtual pad handle.
\param handle The registered handle for the virtual pad.
\return The port number for the virtual pad, or a negative value in case of error.
*/
s32 ioPadLddGetPortNo(s32 handle);

/*! \brief Register a new virtual pad.
\return The handle for the virtual pad, or a negative value in case of error.
*/
s32 ioPadLddRegisterController();

/*! \brief Unregister a virtual pad.
\param handle The registered handle for the virtual pad.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadLddUnregisterController(s32 handle);

/* new in 3.41 */
/*! \brief Get pad information (new format).
\param info Pointer to the pad info structure.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadGetInfo2(padInfo2* info);

/*! \brief Get pad peripheral information.
\param periphInfo Pointer to the pad peripheral info structure.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadPeriphGetInfo(padPeriphInfo* periphInfo);

/*! \brief Get pad peripheral data.
\param port Pad port.
\param periphData Pointer to the pad peripheral data structure.
\return zero if no error occured, nonzero otherwise.
*/
s32 ioPadPeriphGetData(u32 port, padPeriphData* periphData);

/*! \brief Set pad port setting.
\param port Pad port.
\param setting Setting value.
\return zero if no error occured, nonzero otherwise.
\todo confirm this..
*/
s32 ioPadSetPortSetting(u32 port, u32 setting);

#ifdef __cplusplus
	}
#endif

#endif
