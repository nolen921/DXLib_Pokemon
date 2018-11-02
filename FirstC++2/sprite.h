#pragma once

#include<SpriteBatch.h>
#include<SimpleMath.h>
#include<d3d11.h>
#include "player.h"

// ���O���
using namespace DirectX;
using namespace SimpleMath;

// �N���X�錾
class Sprite
{
private:
    static SpriteBatch* sprite_;    // SpriteBatch�N���X�|�C���^

public:
    static bool init();     // ������
    static void begin();    // �`��J�n
    static void end()       { sprite_->End(); } // �`��I��
    static void destroy()   { delete sprite_; } // �j��
    // static void draw( Player player ); // �`��

    // �`��
    static void draw(
        ID3D11ShaderResourceView* Texture,                  // �e�N�X�`��
        const Vector2& Position = Vector2( 0.0F, 0.0F ),    // ���W
        const RECT* Rect = NULL,                            // �`��͈�
        const XMVECTORF32& Color = Colors::White,           // �J���[
        const float Rotation = 0.0F,                        // ��]
        const Vector2& Scale = Vector2( 1.0F, 1.0F ),       // �g�k
        const Vector2& Origin = Vector2( 0.0F, 0.0F ),      // �A���J�[�|�C���g
        const SpriteEffects Effect = SpriteEffects_None,    // �G�t�F�N�g
        const float Depth = 0.0F );                         // �[�x
};