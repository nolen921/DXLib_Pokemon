#pragma once

// Include
#include "field.h"
#include "player.h"

// Class
class Game
{
private:
    Player player_; // �v���C���[�N���X     ��
    Field field_;   // �t�B�[���h�N���X     ���N���X���N���X

public:
    bool init();    // ������
    void update();  // �X�V
    void draw();    // �`��
    void destroy(); // �j��
};