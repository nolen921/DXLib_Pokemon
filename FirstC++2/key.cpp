#include "key.h"

// ���̂̍쐬
Keyboard* Key::key_;
Keyboard::State Key::state_;

bool Key::init()
{
    // �L�[�{�[�h�̃������m��
    key_ = new Keyboard;

    // �������m�ۃ`�F�b�N
    if( !key_ )
    {
        // �G���[
        return false;
    }

    return true;
}

void Key::update()
{
    // ���͏����X�V
    state_ = key_->GetState();
}