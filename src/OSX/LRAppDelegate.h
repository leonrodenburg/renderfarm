//
//  LRAppDelegate.h
//  Renderfarm
//
//  Created by Léon Rodenburg on 10/29/12.
//  Copyright (c) 2012 Léon Rodenburg. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "LRRenderfarmView.h"


@interface LRAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
    LRRenderfarmView *renderfarmView;
}

@property (assign) IBOutlet NSWindow *window;
@property (nonatomic, retain) IBOutlet LRRenderfarmView *renderfarmView;

@end
