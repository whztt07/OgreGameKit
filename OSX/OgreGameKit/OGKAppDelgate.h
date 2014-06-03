//
//  OGKAppDelgate.h
//  OgreGameKit
//
//  Created by Alex on 5/20/14.
//
//

#include "OGKGame.h"

#include "OgrePlatform.h"

#ifdef __OBJC__

#import <Cocoa/Cocoa.h>

@interface OGKAppDelegate : NSObject <NSApplicationDelegate>
{
    NSTimer *mTimer;
}

- (void)renderOneFrame;

@end

#if __LP64__
static id mAppDelegate;
#endif

#endif
