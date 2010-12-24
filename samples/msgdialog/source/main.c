
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

#include <rsx/commands.h>
#include <rsx/nv40.h>
#include <rsx/reality.h>

#include <io/pad.h>

#include <sysmodule/sysmodule.h>

#include "rsxutil.h"

// for msgdialogs
#include "sysutil/events.h"
#include "sysutil/msgdialog.h"

int currentBuffer = 0;

void my_flip()
{
        //tiny3d_Flip();

		flip(currentBuffer); // Flip buffer onto screen
        waitFlip(); // Wait for the last flip to finish, so we can draw to the old buffer
		currentBuffer = !currentBuffer;
}




volatile int dialog_action = 0;

void my_dialog(msgbutton button, void *userdata)
{
    switch(button) {

        case MSGDIALOG_BUTTON_OK:
            dialog_action = 1;
            break;
        case MSGDIALOG_BUTTON_NO:
        case MSGDIALOG_BUTTON_ESCAPE:
            dialog_action = 2;
            break;
        case MSGDIALOG_BUTTON_NONE:
            dialog_action = -1;
            break;
        default:
		    break;
    }
}


void dialog()
{
    int response;
    u32 happypercent;
    u32 moneypercent;

// error code message

    MsgDialogErrorCode(0xBEBACAFE, my_dialog, (void *) 0xEEEE0001, NULL);
    MsgDialogDelayedClose(3000.0f); // 3 seconds

    dialog_action = 0;
    while(dialog_action!=-1)
		{
		sysCheckCallback();my_flip();
		}

    MsgDialogClose();

// yes/no message

    msgtype mdialogyesno = MSGDIALOG_NORMAL | MSGDIALOG_BUTTON_TYPE_YESNO | MSGDIALOG_DISABLE_CANCEL_ON | MSGDIALOG_DEFAULT_CURSOR_NO;

    MsgDialogOpen(mdialogyesno, "Hey!!\nYou are Happy?", my_dialog, (void *) 0x11110001, NULL);

    dialog_action = 0;
    while(!dialog_action)
		{
		sysCheckCallback();my_flip();
		}

    MsgDialogClose();

    response = dialog_action;

// OK message

    msgtype mdialogok = MSGDIALOG_NORMAL | MSGDIALOG_BUTTON_TYPE_OK;
    
    if(response == 1)
        MsgDialogOpen(mdialogok, "I'm glad you're happy :)\nMerry Christmas!!!", my_dialog, (void *) 0x22220001, NULL);
    else
        MsgDialogOpen(mdialogok, "Ok, but removes your vinegar face :p\nIt's Christmas!!!", my_dialog, (void *) 0x22220002, NULL);

    dialog_action = 0;
    while(!dialog_action)
		{
		sysCheckCallback();my_flip();
		}

    MsgDialogClose();

// Single Progress bar 

    msgtype mdialogprogress = MSGDIALOG_SINGLE_PROGRESSBAR;
    
    happypercent = 0;

    MsgDialogOpen(mdialogprogress, "Recharging happiness batteries...", my_dialog, (void *) 0x33330001, NULL);
    MsgDialogProgressBarMessage(PROGRESSBAR_INDEX0, "You're Happy");
    MsgDialogResetProgressBar(PROGRESSBAR_INDEX0);
   
    dialog_action = 0;
    while(!dialog_action)
		{
        MsgDialogIncProgressBar(PROGRESSBAR_INDEX0, happypercent);
		sysCheckCallback();my_flip();
        if(happypercent < 100) happypercent++;
        usleep(100*1000);
		}

    MsgDialogClose();

// Double Progress bar 

    mdialogprogress = MSGDIALOG_DOUBLE_PROGRESSBAR;
    
    moneypercent = 0;

    MsgDialogOpen(mdialogprogress, "Recharging Virtual money...", my_dialog, (void *) 0x33330002, NULL);
    MsgDialogProgressBarMessage(PROGRESSBAR_INDEX0, "You're Happy");
    MsgDialogResetProgressBar(PROGRESSBAR_INDEX0);
    MsgDialogProgressBarMessage(PROGRESSBAR_INDEX1, "Virtual money");
    MsgDialogResetProgressBar(PROGRESSBAR_INDEX1);
   
    dialog_action = 0;
    while(!dialog_action)
		{
        MsgDialogIncProgressBar(PROGRESSBAR_INDEX0, happypercent);
        MsgDialogIncProgressBar(PROGRESSBAR_INDEX1, moneypercent);
		sysCheckCallback();my_flip();
        if(happypercent < 100) happypercent++;
        if(moneypercent < 100) moneypercent++;
        usleep(100*1000);
		}

    MsgDialogClose();

// OK with delay time 

    MsgDialogOpen(mdialogok, "Congratulations!!!\nYou are now happy and you have virtual money :p", my_dialog, (void *) 0x22220003, NULL);
    MsgDialogDelayedClose(3000.0f); // 3 seconds

    dialog_action = 0;
    while(!dialog_action)
		{
		sysCheckCallback();my_flip();
		}

    MsgDialogClose();

// OK with delay time 

    MsgDialogOpen(mdialogok, "Good bye!!", my_dialog, (void *) 0x22220004, NULL);
    MsgDialogDelayedClose(2000.0f); // 2 seconds

    dialog_action = 0;
    while(!dialog_action)
		{
		sysCheckCallback();my_flip();
		}

     MsgDialogClose();
    
}

s32 main(s32 argc, const char* argv[])
{
	
	init_screen();
	ioPadInit(7);

    waitFlip();

    dialog();
	
	return 0;
}

