#pragma once
#include<d3d11.h>
#include<SpriteBatch.h>
#include<WICTextureLoader.h>
#include<SimpleMath.h>
#include<Keyboard.h>
#include"release.h"

using namespace DirectX;
using namespace SimpleMath;

// �N���X�錾
class Player
{
private:
    static Player player_;
    ID3D11ShaderResourceView* texture_; // �e�N�X�`��
    Vector2 position_;                  // ���W
    float speed_;                       // �ړ����x
    RECT rect;                          // �`��͈�
    float scale_;                       // �X�P�[���l
    SpriteEffects flip_;                // ���]
    int animation_no_;                  // �e�N�X�`���̔ԍ�
    int animation_counter_;             // �A�j���[�V�����p���[�v�J�E���g
    int direction_;                     // �L�����̌���
    int key_counter_;                   // ���͗p���[�v�J�E���^�[
    bool move_;                         // �ړ����t���O0/1
    int move_counter_;                  // �ړ��p���[�v�J�E���^�[
    bool dash_;                         // �_�b�V���t���O0/1
    int jump_switch_;                   // �W�����v�X�C�b�`(0�`3)
    static int masu_position_x_, masu_position_y_;         // �}�X�P�ʂ̍��W
    static bool collision_;             // �Փ˂��Ă���
    bool enterPokecen_;                 // �|�P�����Z���^�[�ɓ���

public:
    Player();                           // �R���X�g���N�^
    ~Player();                          // �f�X�g���N�^

    // ������
    bool init( const wchar_t* FileName );

    // �X�V����
    void update();

    // �A�j���[�V����
    static void animation();

    // �}�X�P�ʂ̃v���C���[X���W���擾
    static int getMasuPositionX() { return masu_position_x_; }
    // �}�X�P�ʂ̃v���C���[Y���W���擾
    static int getMasuPositionY() { return masu_position_y_; }

    // �}�X�P�ʂ̃v���C���[X���W��ݒ�
    static void setMasuPositionX(int n) { masu_position_x_ = n; }
    // �}�X�P�ʂ̃v���C���[Y���W��ݒ�
    static void setMasuPositionY(int n) { masu_position_y_ = n; }

    // move��ݒ�
    static void setMove( bool a );

    // jump_switch��ݒ�
    static void setJumpSwitch( int n );

    // collision��ݒ�
    static void setCollision( bool a ) { collision_ = a; }

    // dash_��Ԃ��֐�
    bool getDash() { return dash_; }

    // �`��
    void draw();

    void destroy();
};