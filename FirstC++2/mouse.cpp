#include "mouse.h"

// ���̂̍쐬
Mouse MyMouse::mouse_;
Mouse::State MyMouse::state_;

MyMouse::MyMouse()
{
    // Mouse::MODE_ABSOLUTE�c��΍��W���[�h
    // Mouse::MODE_RELATIVE�c���΍��W���[�h
    mouse_.SetMode( Mouse::MODE_ABSOLUTE );
}

void MyMouse::update()
{
    // ���΃��[�h�Ŏg�p����Ƃ���Mouse�N���X�ɃE�B���h�E�n���h����n���K�v������
    // mouse.SetWindow( hWnd );

    // ���͏����X�V
    state_ = mouse_.GetState();
}