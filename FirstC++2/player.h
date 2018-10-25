#pragma once
#include<d3d11.h>
#include<SpriteBatch.h>
#include<WICTextureLoader.h>
#include<SimpleMath.h>
#include<Keyboard.h>

using namespace DirectX;
using namespace SimpleMath;

// �N���X�錾
class Player
{
private:
    ID3D11ShaderResourceView* texture_; // �e�N�X�`��
    Vector2 position_;                  // ���W
    float speed_;                       // �ړ����x
    RECT rect;                          // �`��͈�
    void animation();
    int animation_no_;                  // �e�N�X�`���̔ԍ�
    int animation_counter_;             // �A�j���[�V�����p���[�v�J�E���g
    int direction_;                     // �L�����̌���

public:
    Player();                           // �R���X�g���N�^
    ~Player();                          // �f�X�g���N�^

    // ������
    bool init( const wchar_t* FileName );

    // �X�V����
    void update(const Keyboard::State* pState);

    // �`��
    void draw();

    void destroy();
};