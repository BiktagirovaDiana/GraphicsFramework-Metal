//
//  RendererAdapter.h
//  MetalApp
//
//  Created by Macbook on 24.03.2026.
//

#ifndef RendererAdapter_h
#define RendererAdapter_h

#import "QuartzCore/CAMetalLayer.h"
#import "Metal/MTLDevice.h"
#import "Renderer.hpp"

@interface RendererAdapter : NSObject
-(void)Draw:(id <CAMetalDrawable>) drawable device: (id <MTLDevice>) device;

@end

#endif /* RendererAdapter_h */
