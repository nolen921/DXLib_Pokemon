#pragma once

#include<Windows.h>
#include<Keyboard.h>

using namespace DirectX;

// Class
class Key
{
private:
    static Keyboard key_;     // �L�[�{�[�h�N���X
    static Keyboard::State state_;   // �L�[�{�[�h���͂̏��
public:
    static void update();  // �X�V����
    static const Keyboard::State& getState() { return state_; } // ���͏���Ԃ�
};