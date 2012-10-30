//
//  LRAppDelegate.mm
//  Renderfarm
//
//  Created by Léon Rodenburg on 10/29/12.
//  Copyright (c) 2012 Léon Rodenburg. All rights reserved.
//

#import "LRAppDelegate.h"

@implementation LRAppDelegate

@synthesize window;
@synthesize renderfarmView;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    [renderfarmView prepare];
}

@end
