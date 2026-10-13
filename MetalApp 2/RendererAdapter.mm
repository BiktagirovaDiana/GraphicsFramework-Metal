//
//  RendererAdapter.mm
//  MetalApp
//
//  Created by Macbook on 24.03.2026.
//

//#import <Foundation/Foundation.h>
#import "RendererAdapter.h"
#include "Controller.hpp"

@implementation RendererAdapter
{
    Renderer *renderer;
    Controller *controller;
}

- (instancetype)initWithDevice:(id<MTLDevice>)device
{
    self = [super init];
    if (self)
    {
        controller = new Controller();
        
        renderer = new Renderer((__bridge MTL::Device *)device, controller);
    }
    return self;
}

-(void)KeyDown:(int)key
{
    controller->KeyDown(static_cast<Key>(key));
}

-(void)KeyUp:(int)key
{
    controller->KeyUp(static_cast<Key>(key));
}

-(void)Draw:(id<CAMetalDrawable>)drawable device:(id<MTLDevice>)device
{
    renderer->Draw((__bridge CA::MetalDrawable *)drawable);
}

- (void)dealloc
{
    delete renderer;
    delete controller;
}
@end
