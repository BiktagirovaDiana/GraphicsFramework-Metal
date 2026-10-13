//
//  Controller.hpp
//  MetalApp 2
//
//  Created by Macbook on 11.10.2026.
//
#pragma once
enum class Key
{
    None,
    W,
    A,
    S,
    D,
    Space,
    Shift
};

class Controller
{
public:
    void KeyDown(Key key);
    void KeyUp(Key key);
    bool IsKeyDown(Key key) const;

private:
    bool wPressed = false;
    bool aPressed = false;
    bool sPressed = false;
    bool dPressed = false;
    bool spacePressed = false;
    bool shiftPressed = false;
};


