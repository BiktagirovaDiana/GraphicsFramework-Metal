//
//  RendererAdapter.mm
//  MetalApp
//
//  Created by Macbook on 24.03.2026.
//

//#import <Foundation/Foundation.h>
#import "RendererAdapter.h"

@implementation RendererAdapter
-(void)Draw:(id <CAMetalDrawable>) drawable device: (id <MTLDevice>) device
{
    Renderer renderer((__bridge MTL::Device *)device);
    renderer.Draw((__bridge CA::MetalDrawable *)drawable, (__bridge MTL::Device *)device);
}
@end
