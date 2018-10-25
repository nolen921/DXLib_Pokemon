#pragma once

// Include
#include <CommonStates.h>

// ���O���
using namespace DirectX;

// Class
class Common
{
private:
    static CommonStates* state_; // CommonStates�N���X�|�C���^

public:
    static bool init();                         // ������
    static void destroy() { delete state_; }    // �j��
    static CommonStates* getState() { return state_; }  // CommonState�|�C���^��Ԃ�
};