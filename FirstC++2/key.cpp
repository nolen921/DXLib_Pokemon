#include "key.h"

// ���̂̍쐬
Keyboard Key::key_;
Keyboard::State Key::state_;

void Key::update()
{
    // ���͏����X�V
    state_ = key_.GetState();
}