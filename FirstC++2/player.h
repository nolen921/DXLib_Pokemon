#pragma once
#include<d3d11.h>
#include<SpriteBatch.h>
#include<WICTextureLoader.h>
#include<SimpleMath.h>

using namespace DirectX;
using namespace SimpleMath;

// �N���X�錾
class Player
{
private:
    ID3D11ShaderResourceView* texture_; // �e�N�X�`��
    Vector2 position_;                  // ���W
    float speed_;                       // �ړ����x

public:
    Player();                           // �R���X�g���N�^
    ~Player();                          // �f�X�g���N�^

    // ������
    bool init( const wchar_t* FileName, ID3D11Device* Device, ID3D11DeviceContext* Context );

    // �X�V����
    void update();

    // �`��
    void draw( SpriteBatch* Sprite );

    void destroy();
};