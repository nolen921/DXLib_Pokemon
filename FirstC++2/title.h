#pragma once

#include <d3d11.h>
#include "release.h"

class Title
{
private:
    ID3D11ShaderResourceView* texture_; // �e�N�X�`��

public:
    // �R���X�g���N�^
    Title() : texture_( NULL ) {}

    bool init();    // ������
    bool update();  // �X�V
    void draw();    // �`��
    void destroy(); // �j��
};

#if 0
// �Q�[���N���X������
    Game game;
    if( !game.init() )
    {
        // �G���[
        return 0;
    }
// �Q�[���N���X�A�b�v�f�[�g
                game.update();

                // �Q�[���N���X�`��
                game.draw();

#endif