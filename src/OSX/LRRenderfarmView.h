//
//  LRRenderView.h
//  Renderfarm
//
//  Created by Léon Rodenburg on 10/29/12.
//  Copyright (c) 2012 Léon Rodenburg. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "Kernel.h"
#include "World.h"
#include "Cube.h"

#include <vector>

#define kWidth 800
#define kHeight 600
#define kNearView 1.0f
#define kFarView 500.0f
#define kFieldOfView RFMathDegToRad(45.0f)

@interface LRRenderfarmView : NSView {
    RFCore::Kernel* pKernel;
    RFGeometry::World* pWorld;
    std::vector<RFGeometry::Geometry*>* pGeometry;
    
    unsigned int* pBuffer;
    
    NSTimer* timer;
    
    BOOL rendering;
}

-(void)prepare;
-(void)initialize;
-(void)run:(NSTimer*)t;

@end
