#include "pad.h"

// ���Ԃ̐錾
GamePad Pad::pad_;
GamePad::State Pad::state_;

// �X�V����
void Pad::update()
{
    // ���͂��擾
    // �����ŉ��Ԗڂ̃R���g���[���̓��͂���邩���߂�(�����Ȃ���ꍇ�A�z����g��)
    state_ = pad_.GetState( 0 );
}