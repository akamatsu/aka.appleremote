/* Carbon entry point and C-callable wrapper functions */

#import "AppleRemote.h"
#include "AppleRemoteWrapper.h"

AppleRemote	*gAppleRemote = NULL;

Boolean initAppleRemote(void)
{
	if (gAppleRemote == NULL)
	{	
		gAppleRemote = [AppleRemote sharedRemote];
		if (gAppleRemote != NULL)
			return	true;
	}
	
	return (false);
}

void terminateAppleRemote(void)
{
	if (gAppleRemote != NULL)
	{
		[gAppleRemote dealloc];
		gAppleRemote = NULL;
	}
}

void setExclusiveMode(Boolean flag)
{
	[gAppleRemote setOpenInExclusiveMode:flag];
}

void startListening(void)
{
	[gAppleRemote startListening: 0];
}

void stopListening(void)
{
	[gAppleRemote stopListening: 0];
}

void setCallBack(void *func, void *refCon)
{
	[gAppleRemote setCallBack:(CallBackType)func refCon:refCon];
}