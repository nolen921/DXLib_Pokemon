#pragma once

#include <Windows.h>
#include <Mouse.h>

using namespace DirectX;

class MyMouse
{
private:
    static Mouse mouse_;
    static Mouse::State state_;

public:
    MyMouse();
    static void update();
    static const Mouse::State& getState() { return state_; }    // Mouse“ü—Í‚ðŽæ“¾
};