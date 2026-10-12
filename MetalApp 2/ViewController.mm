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
{
    RendererAdapter *rendererAdapter;
}

- (void) viewDidLoad
{
    [super viewDidLoad];
    
    MTKView *view = (MTKView*)self.view;
    view.device = MTLCreateSystemDefaultDevice(); //назначение видеокарты
    view.delegate = self;
    view.paused = NO;
    view.enableSetNeedsDisplay = NO;
    view.preferredFramesPerSecond = 60;
    
    rendererAdapter = [[RendererAdapter alloc] initWithDevice:view.device]; //выделяем память
}

- (void)drawInMTKView:(MTKView *)view
{
    if (view.currentDrawable == nil)
    {
        return;
    }

    [rendererAdapter Draw:view.currentDrawable device:view.device];
}

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size
{
}


- (void)viewDidAppear
{
    [super viewDidAppear];

    self.view.window.acceptsMouseMovedEvents = YES;
    BOOL isFirstResponder = [self.view.window makeFirstResponder:self];
    NSLog(@"ViewController first responder: %@", isFirstResponder ? @"YES" : @"NO");
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (void)keyDown:(NSEvent *)event
{
    switch (event.keyCode)
    {
        case 13:
            [rendererAdapter KeyDown:1]; // W
            break;
        case 0:
            [rendererAdapter KeyDown:2]; // A
            break;
        case 1:
            [rendererAdapter KeyDown:3]; // S
            break;
        case 2:
            [rendererAdapter KeyDown:4]; // D
            break;
    }
}

- (void)keyUp:(NSEvent *)event
{
    switch (event.keyCode)
    {
        case 13:
            [rendererAdapter KeyUp:1]; // W
            break;
        case 0:
            [rendererAdapter KeyUp:2]; // A
            break;
        case 1:
            [rendererAdapter KeyUp:3]; // S
            break;
        case 2:
            [rendererAdapter KeyUp:4]; // D
            break;
    }
}

@end
