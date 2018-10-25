#pragma once

#include<Windows.h>
#include<Keyboard.h>

using namespace DirectX;

// Class
class Key
{
private:
    static Keyboard* key_;     // �L�[�{�[�h�N���X
    static Keyboard::State state_;   // �L�[�{�[�h���͂̏��
public:
    static bool init();     // ������
    static void update();   // �X�V
    static void destroy() { delete(key_); }  // �j��

    // �L�[�{�[�h���͂̎擾
    static Keyboard::State* getNyuryoku() { return &state_; }
};