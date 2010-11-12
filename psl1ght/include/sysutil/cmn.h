#pragma once

#include <psl1ght/types.h>

EXTERN_BEGIN

/* System Event for sysutilCallback status parameter */
#define SYSUTIL_REQUEST_EXIT		0x0101
#define SYSUTIL_DRAWING_BEGIN		0x0121
#define SYSUTIL_DRAWING_END			0x0122
#define SYSUTIL_SYSTEM_MENU_OPEN	0x0131
#define SYSUTIL_SYSTEM_MENU_CLOSE	0x0132
#define SYSUTIL_BGMPLAYBACK_PLAY	0x0141
#define SYSUTIL_BGMPLAYBACK_STOP	0x0142

/* Function Pointer for sysutilCallback
u32 userdata = void* userdata
 */
typedef void (*sysutilCallback)(const u64 status, const u64 param, u32 userdata);

/**
 * \brief Register system event callback
 *
 * \param[in] slot : callback slot number (between 0 to 3)
 * \param[in] func : callback function to register
 * \param[in] userdata : user data pointer passed to callback function
 * \return 0 if OK or else error code
 */
s32 sysutilRegisterCallback(const u32 slot, const sysutilCallback func, void* userdata);

/**
 * \brief Unregister system event callback
 *
 * \param[in] slot : callback slot number (between 0 to 3)
 * \return 0 if OK or else error code
 */
s32 sysutilUnregisterCallback(const u32 slot);

/**
 * \brief Check system event and call callback
 *
 * \return 0 if OK or else error code
 */
s32 sysutilCheckCallback(void);

EXTERN_END
