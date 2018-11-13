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
    Game();         // �R���X�g���N�^
    ~Game();        // �f�X�g���N�^
    bool init();    // ������
    bool update();  // �X�V
    void draw();    // �`��
    void destroy(); // �j��
};