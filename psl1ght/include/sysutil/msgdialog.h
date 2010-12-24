#pragma once

#include <psl1ght/types.h>
#include <stdlib.h>

EXTERN_BEGIN


typedef enum {

    MSGDIALOG_ERROR                 = 0,
    MSGDIALOG_NORMAL                = 1,
    MSGDIALOG_MUTE_ON	            = 2,
    MSGDIALOG_BACKGROUND_INVISIBLE  = 4,
    MSGDIALOG_BUTTON_TYPE_YESNO     = 16,
    MSGDIALOG_BUTTON_TYPE_OK        = 32,
    MSGDIALOG_DISABLE_CANCEL_ON	    = 128,
    MSGDIALOG_DEFAULT_CURSOR_NO     = 256,

    MSGDIALOG_SINGLE_PROGRESSBAR    = 4096,
    MSGDIALOG_DOUBLE_PROGRESSBAR    = 8192

} msgtype;

typedef enum {

	MSGDIALOG_BUTTON_NONE = -1,
	MSGDIALOG_BUTTON_INVALID,
	MSGDIALOG_BUTTON_OK,
	MSGDIALOG_BUTTON_YES  =  1,
	MSGDIALOG_BUTTON_NO,
	MSGDIALOG_BUTTON_ESCAPE

} msgbutton;

typedef void (*MsgDialog)(msgbutton button, void *userdata);

s32 MsgDialogOpen(msgtype type, const char * msg, MsgDialog func, void * userdata, void *unused);
s32 MsgDialogOpen_ex(msgtype type, const char * msg, opd32 * func, void * userdata, void *unused);
s32 MsgDialogClose(void);
s32 MsgDialogDelayedClose(float ms);

s32 MsgDialogErrorCode(u32 errorcode, MsgDialog func, void * userdata, void *unused);
s32 MsgDialogErrorCode_ex(u32 errorcode, opd32 * func, void * userdata, void *unused);

#define PROGRESSBAR_INDEX0 0
#define PROGRESSBAR_INDEX1 1

s32 MsgDialogProgressBarMessage(u32 index, const char * msg);
s32 MsgDialogResetProgressBar(u32 index);
s32 MsgDialogIncProgressBar(u32 index, u32 percent);

EXTERN_END
