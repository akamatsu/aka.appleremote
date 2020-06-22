//
//  MainController.h
//  AppleRemote
//
//  Created by Martin Kahr on 16.03.06.
//  Copyright 2006 martinkahr.com. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "AppleRemote.h"

@interface MainController : NSObject {
	IBOutlet NSView*		feedbackView;
	IBOutlet NSTextField*	feedbackText;
}

- (AppleRemote*) appleRemote;

@end
