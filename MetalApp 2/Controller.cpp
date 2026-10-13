//
//  Controller.cpp
//  MetalApp 2
//
//  Created by Macbook on 11.10.2026.
//

#include "Controller.hpp"

void Controller::KeyDown(Key key)
{
    switch (key)
    {
        case Key::W:
            wPressed = true;
            break;
        case Key::A:
            aPressed = true;
            break;
        case Key::S:
            sPressed = true;
            break;
        case Key::D:
            dPressed = true;
            break;
        case Key::Space:
            spacePressed = true;
            break;
        case Key::Shift:
            shiftPressed = true;
            break;
        case Key::None:
            break;
    }
}

void Controller::KeyUp(Key key)
{
    switch (key)
    {
        case Key::W:
            wPressed = false;
            break;
        case Key::A:
            aPressed = false;
            break;
        case Key::S:
            sPressed = false;
            break;
        case Key::D:
            dPressed = false;
            break;
        case Key::Space:
            spacePressed = false;
            break;
        case Key::Shift:
            shiftPressed = false;
            break;
        case Key::None:
            break;
    }
}

bool Controller::IsKeyDown(Key key) const
{
    switch (key)
    {
        case Key::W:
            return wPressed;
        case Key::A:
            return aPressed;
        case Key::S:
            return sPressed;
        case Key::D:
            return dPressed;
        case Key::Space:
            return spacePressed;
        case Key::Shift:
            return shiftPressed;
        case Key::None:
            return false;
    }
}
