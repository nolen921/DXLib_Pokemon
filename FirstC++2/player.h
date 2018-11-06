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
    int key_counter_;                   // ���͗p���[�v�J�E���^�[
    bool move_;                         // �ړ����t���O0/1
    int move_counter_;                  // �ړ��p���[�v�J�E���^�[
    bool dash_;                         // �_�b�V���t���O0/1
    bool jump_down_flag_;               // �W�����v�t���O��
    bool jump_right_flag_;              // �W�����v�t���O�E
    bool jump_left_flag_;               // �W�����v�t���O��
    static int masu_position_x_, masu_position_y_;         // �}�X�P�ʂ̍��W
    bool collision_;                    // �Փ˂��Ă���

public:
    Player();                           // �R���X�g���N�^
    ~Player();                          // �f�X�g���N�^

    // ������
    bool init( const wchar_t* FileName );

    // �X�V����
    void update(const Keyboard::State* pState);

    // �}�X�P�ʂ̃v���C���[X���W���擾
    static int getMasuPositionX() { return masu_position_x_; }
    // �}�X�P�ʂ̃v���C���[Y���W���擾
    static int getMasuPositionY() { return masu_position_y_; }

    // dash_��Ԃ��֐�
    bool getDash() { return dash_; }

    // �`��
    void draw();

    void destroy();
};