#pragma once

#define POKECEN_POS 7040.0F

#include"direct3d.h"
#include"sprite.h"

// �\����
struct Parts
{
    Vector2 position;   // ���W
    RECT trim;          // �`��͈�
    int id;             // �p�[�c�ԍ�
    int layer;          // ���C���[�ԍ�

    // �R���X�g���N�^
    Parts()
    {
        position = Vector2( 0.0F, 0.0F );
        trim = RECT{ 0 };
        id = 0;
        layer = 0;
    }
};

// �N���X
class Field
{
private:
    ID3D11ShaderResourceView* texture_;         // �e�N�X�`��
    ID3D11ShaderResourceView* texture2_;        // �e�N�X�`��
    static int width_, height_;                 // �}�b�v�����c��
    static int pokecen_width_, pokecen_height_; // �}�b�v�����c��
    static int LayerCount_;                     // ���C���[��
    static int Pokecen_LayerCount_;             // �|�P�Z�����C���[��
    static Parts* parts_;                       // �p�[�c�\���̃|�C���^
    static float offset_x_, offset_y_;          // �X�N���[���p
    static int index_;                          // �����̃p�[�c�ԍ�

public:
    Field();        // �R���X�g���N�^
    ~Field() {};    // �f�X�g���N�^
    bool init();    // ������
    static void move_x( const float x );    // �X�V
    static void move_y( const float y );    // �X�V
    static void set_x( const float x );     // �w��̃I�t�Z�b�g�ɂ���
    static void set_y( const float y );     // �w��̃I�t�Z�b�g�ɂ���
    static int getPartsId( int i );         // �p�[�c�ԍ����擾
    static void setPartsTrim( int i, int l, int r, int t, int b );       // �p�[�c�̕`��͈͂�ݒ�
    static int getLayer( int i );           // ���C���[�ԍ����擾
    static int getMapWidth();               // �}�b�v�������擾
    static int getMapHeight();              // �}�b�v�c�����擾
    static int getIndex();                  // �C���f�b�N�X���擾
    float getOffsetX() { return offset_x_; }  // �I�t�Z�b�gx���擾
    float getOffsetY() { return offset_y_; }  // �I�t�Z�b�gy���擾
    void draw(int layer, bool drawID );                   // �`��
    void destroy();                         // �j��
};