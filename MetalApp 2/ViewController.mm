//
//  ViewController.mm
//  MetalApp
//
//  Created by Macbook on 24.03.2026.
//

#import <Foundation/Foundation.h>
#import "ViewController.h"
#import "RendererAdapter.h"

@implementation ViewController

- (void) viewDidLoad
{
    [super viewDidLoad];
    
    MTKView *view = (MTKView*)self.view;
    view.device = MTLCreateSystemDefaultDevice(); //назначение видеокарты
    
    RendererAdapter *rendererAdapter = [[RendererAdapter alloc] init]; //выделяем память
    [rendererAdapter Draw:view.currentDrawable device:view.device];
}


@end
