//
//  MainController.m
//  AppleRemote
//
//  Created by Martin Kahr on 16.03.06.
//  Copyright 2006 martinkahr.com. All rights reserved.
//

#import "MainController.h"


@implementation MainController

- (void) awakeFromNib 
{
	[[AppleRemote sharedRemote] setDelegate: self];
}

- (AppleRemote*) appleRemote 
{
	return [AppleRemote sharedRemote];
}


// delegate methods for AppleRemote
- (void) appleRemoteButton: (AppleRemoteCookieIdentifier)buttonIdentifier pressedDown: (BOOL) pressedDown 
{
	NSString* buttonName=nil;
	NSString* pressed=@"";
	
	switch(buttonIdentifier) {
		case kRemoteButtonVolume_Plus:
			buttonName = @"Volume up";
			if (pressedDown) pressed = @"(down)"; else pressed = @"(up)";
			break;
		case kRemoteButtonVolume_Minus:
			buttonName = @"Volume down";
			if (pressedDown) pressed = @"(down)"; else pressed = @"(up)";
			break;			
		case kRemoteButtonMenu:
			buttonName = @"Menu";
			break;			
		case kRemoteButtonPlay:
			buttonName = @"Play";
			break;			
		case kRemoteButtonRight:	
			buttonName = @"Right";
			break;			
		case kRemoteButtonLeft:
			buttonName = @"Left";
			break;			
		case kRemoteButtonRight_Hold:
			buttonName = @"Right holding";	
			if (pressedDown) pressed = @"(down)"; else pressed = @"(up)";
			break;	
		case kRemoteButtonLeft_Hold:
			buttonName = @"Left holding";		
			if (pressedDown) pressed = @"(down)"; else pressed = @"(up)";
			break;			
		case kRemoteButtonPlay_Sleep:
			buttonName = @"Play (sleep mode)";
			break;			
		default:
			NSLog(@"Unmapped event for button %d", buttonIdentifier); 
			break;
	}	
	[feedbackText setStringValue:[NSString stringWithFormat:@"%@ %@", buttonName, pressed]];
	
	// delegate to view
	[feedbackView appleRemoteButton:buttonIdentifier pressedDown:pressedDown];
}

@end
