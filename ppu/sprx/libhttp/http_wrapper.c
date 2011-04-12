#include <stdio.h>
#include <stdlib.h>
#include <ppu-asm.h>

#include <http/http.h>

extern s32 httpClientSetAuthenticationCallbackEx(httpClientId clientId,opd32 *opd,void *usrArg);
extern s32 httpClientSetTransactionStateCallbackEx(httpClientId clientId,opd32 *opd,void *usrArg);
extern s32 httpClientSetRedirectCallbackEx(httpClientId clientId,opd32 *opd,void *usrArg);

s32 httpClientSetAuthenticationCallback(httpClientId clientId,httpAuthenticationCallback cb,void *usrArg)
{
	return httpClientSetAuthenticationCallbackEx(clientId,(opd32*)__get_opd32(cb),usrArg);
}

s32 httpClientSetTransactionStateCallback(httpClientId clientId,httpTransactionStateCallback cb,void *usrArg)
{
	return httpClientSetTransactionStateCallbackEx(clientId,(opd32*)__get_opd32(cb),usrArg);
}

s32 httpClientSetRedirectCallback(httpClientId clientId,httpRedirectCallback cb,void *usrArg)
{
	return httpClientSetRedirectCallbackEx(clientId,(opd32*)__get_opd32(cb),usrArg);
}
