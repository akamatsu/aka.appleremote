/* RemoteFeedbackView */

#import <Cocoa/Cocoa.h>
#import "AppleRemote.h"

@interface RemoteFeedbackView : NSView
{
	NSImage* remoteImage;
	AppleRemoteCookieIdentifier lastButtonIdentifier;
	BOOL drawn;
	BOOL clearAfterDraw;
}

- (void) appleRemoteButton: (AppleRemoteCookieIdentifier)buttonIdentifier pressedDown: (BOOL) pressedDown;

@end
