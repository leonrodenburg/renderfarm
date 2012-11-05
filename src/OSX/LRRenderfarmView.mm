//
//  LRRenderView.mm
//  Renderfarm
//
//  Created by Léon Rodenburg on 10/29/12.
//  Copyright (c) 2012 Léon Rodenburg. All rights reserved.
//

#import "LRRenderfarmView.h"

@implementation LRRenderfarmView

/**
 * Initalize the world by adding geometry.
 */
-(void)initialize
{
    // Initialize geometry and models
    RFGeometry::Cube* pCube = new RFGeometry::Cube(1.0f, RFMath::Vector3(1.7f, 1.0f, 6.0f));
    pGeometry->push_back(pCube);
    
    RFGeometry::Cube* pCube5 = new RFGeometry::Cube(1.0f, RFMath::Vector3(-1.0f, -1.0f, 10.0f));
    pGeometry->push_back(pCube5);
    
    RFGeometry::Cube* pCube2 = new RFGeometry::Cube(1.0f, RFMath::Vector3(-3.0f, -2.0f, 10.0f));
    pGeometry->push_back(pCube2);
    
    RFGeometry::Cube* pCube3 = new RFGeometry::Cube(1.0f, RFMath::Vector3(2.0f, -2.5f, 10.0f));
    pGeometry->push_back(pCube3);
    
    RFGeometry::Cube* pCube4 = new RFGeometry::Cube(1.0f, RFMath::Vector3(4.0f, 1.0f, 15.0f));
    pGeometry->push_back(pCube4);
}

/**
 * Initialize view.
 *
 * @param frame
 *
 * @return Initialized view
 */
-(id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    
    if (self) {
        
    }
    
    return self;
}

/**
 * Called when the window is destroyed.
 */
-(void)dealloc
{
    for(unsigned int i = 0; i < pGeometry->size(); ++i)
    {
        delete pGeometry->at(i);
    }
    delete pGeometry;
    
    if(pWorld)
    {
        delete pWorld;
    }
    
    if(pKernel)
    {
        delete pKernel;
    }
    
    [super dealloc];
}

/**
 * Called when the dirty rect should be redrawn.
 *
 * @param dirtyRect
 */
-(void)drawRect:(NSRect)dirtyRect
{
    
}

/**
 * Prepare for rendering by creating the kernel and world.
 */
-(void)prepare
{
#ifdef DEBUG
    std::cout << "DEBUG BUILD - BE PREPARED TO SEE OUTPUT!" << std::endl;
#else
    std::cout << "RELEASE BUILD - CONSOLE OUTPUT SUPPRESSED" << std::endl;
#endif
    
    // Create world and kernel
    pWorld = new RFGeometry::World();
    
#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log((char *)"Created world...");
#endif
    
    pKernel = new RFCore::Kernel(pWorld, kNearView, kFarView, kFieldOfView, kWidth, kHeight);
    
#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log((char *)"Attached world to kernel...");
#endif
    
    pGeometry = new std::vector<RFGeometry::Geometry*>();
    
    // Initialize geometry
    [self initialize];
    
    for(unsigned int i = 0; i < pGeometry->size(); ++i)
    {
        pWorld->AddGeometry(pGeometry->at(i));
    }
    
#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log((char *)"Added geometry to world...");
#endif
    
    // Start timer and main loop
    rendering = NO;
    timer = [NSTimer timerWithTimeInterval:(1 / 60) target:self selector:@selector(run:) userInfo:nil repeats:YES];
    [[NSRunLoop mainRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
    
    [self setNeedsDisplay:YES];
    
#ifdef DEBUG
    RFCore::Logger::GetLogger()->Log((char *)"Started message loop, time to render!");
#endif
}

/**
 * Main loop, telling the kernel to render and invalidating
 * the view.
 */
-(void)run:(NSTimer*)t
{
    if(!rendering)
    {
        pBuffer = pKernel->Run();
        rendering = YES;
        
        // Get context
        void* currentContext = [[NSGraphicsContext currentContext] graphicsPort];
        
        // Draw pixel data to new bitmap context
        CGContextRef context = 0;
        CGImageRef image = 0;
        CGColorSpaceRef colorSpace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
        CGRect bounds = CGRectMake(0, 0, kWidth, kHeight);
        
        context = CGBitmapContextCreate(NULL, kWidth, kHeight, 8, kWidth * 4 * 8, colorSpace, kCGImageAlphaNoneSkipLast);
        char* data = (char*)CGBitmapContextGetData(context);
        
        for(int y = 0; y < kHeight; ++y)
        {
            for(int x = 0; x < kWidth; ++x)
            {
                data[y * (kWidth * 4 * 8) + (x * 4)] = pBuffer[y * (kWidth * 3) + (x * 3)];
                data[y * (kWidth * 4 * 8) + (x * 4) + 1] = pBuffer[y * (kWidth * 3) + (x * 3) + 1];
                data[y * (kWidth * 4 * 8) + (x * 4) + 2] = pBuffer[y * (kWidth * 3) + (x * 3) + 2];
                data[y * (kWidth * 4 * 8) + (x * 4) + 3] = 0;
            }
        }
        
        image = CGBitmapContextCreateImage(context);
        
        CGContextDrawImage((CGContextRef)currentContext, bounds, image);
        
        CGColorSpaceRelease(colorSpace);
        CGContextRelease(context);
        CGImageRelease(image);
        
        rendering = NO;
    }
}

@end
