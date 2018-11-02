#include "field.h"
#include "texture.h"
#include "sprite.h"
#include "error.h"

Parts* Field::parts_;
float Field::offset_x_;
float Field::offset_y_;
int Field::width_;
int Field::height_;
int Field::LayerCount_;

// �R���X�g���N�^
Field::Field()
{
    texture_ = NULL;
    parts_ = NULL;
    width_ = 0;
    height_ = 0;
    offset_x_ = 0.0F;
    offset_y_ = 0.0F;
}

// ������
bool Field::init()
{
    // �e�N�X�`���̓ǂݍ���
    if(!(texture_ = Texture::load( L"pokemon_rse.png" )))
    {
        // �G���[
        return false;
    }

    // FMF�t�@�C�����J��
    FILE* fp = fopen( "pokemon_map.fmf", "rb" );

    if( !fp )
    {
        // �G���[
        Error::showDialog( "map.fmf���J���܂���ł����B" );
        return false;
    }

    // �擪8Byte���X�L�b�v
    fseek( fp, 8L, SEEK_SET );

    // �}�b�v�̉����Əc�����擾
    fread( &width_, sizeof( int ), 1, fp );
    fread( &height_, sizeof( int ), 1, fp );

    // �擪18Byte���X�L�b�v
    fseek( fp, 18L, SEEK_SET );

    // ���C���[�����擾
    fread( &LayerCount_, sizeof( char ), 1, fp );

    // Parts�\���̂̃��������m��
    parts_ = new Parts[ width_ * height_ * LayerCount_ ];

    // NULL�`�F�b�N
    if( !parts_ )
    {
        // �G���[
        Error::showDialog( "�p�[�c�\���̂̃������m�ۂɎ��s���܂����B" );
        return false;
    }

    // FMF�w�b�_�[�������X�L�b�v
    fseek( fp, 20L, SEEK_SET );

    // �S�p�[�c�f�[�^���i�[
    for( int i = 0; i < LayerCount_; i++ )
    {
        for( int j = width_ * height_ * i; j < width_ * height_* (i+1); j++ )
        {
            // �ԍ��̎擾
            fread( &parts_[ j ].id, sizeof( char ), 1, fp );

            // �`��͈͂̐ݒ�
            parts_[ j ].trim.left = parts_[ j ].id % 16 * 64L;
            parts_[ j ].trim.top = parts_[ j ].id / 16 * 64L;
            parts_[ j ].trim.right = parts_[ j ].trim.left + 64L;
            parts_[ j ].trim.bottom = parts_[ j ].trim.top + 64L;

            // ���W�ݒ�
            parts_[ j ].position.x = static_cast<float>(64.0F * (j % width_));
            parts_[ j ].position.y = static_cast<float>(64.0F * ((j % (width_ * height_)) / width_));
        }
    }

    // �t�@�C�������
    fclose( fp );

    return true;
}

// �X�V
void Field::move_x( const float x )
{
    offset_x_ += x;
}

void Field::move_y( const float y )
{
    offset_y_ += y;
}

// �p�[�c�ԍ����擾
int Field::getPartsId(int i)
{
    return parts_[ i ].id;
}

// ���C���[�ԍ����擾
int Field::getLayer( int i )
{
    return parts_[ i ].layer;
}

// �}�b�v�������擾
int Field::getMapWidth() 
{
    return width_;
}

// �}�b�v�c�����擾
int Field::getMapHeight()
{
    return height_;
}

int Field::getIndex()
{
    int x = static_cast<int>(offset_x_ / 64 + 9);
    int y = static_cast<int>(offset_y_ / 64 + 5);
    index_ = (y*width_) + x;

    return index_;
}

// �`��
void Field::draw(int n)
{
    for( int i = width_ * height_ * n; i < width_ * height_ * (n+1); i++ )
    {
        if( i % width_ <= Player::getMasuPositionX() - 10 || i % width_ >= Player::getMasuPositionX() + 9 )
        {
            continue;
        }
        if( i % (width_ * height_) / width_ <= Player::getMasuPositionY() - 6 || i % (width_ * height_) / width_ >= Player::getMasuPositionY() + 4 )
        {
            continue;
        }

        XMVECTORF32 color = Colors::White;
        if( i == ((offset_y_ / 64 + 6)* width_) + (offset_x_ / 64 + 10) )
            color = Colors::Red;

        Sprite::draw( texture_, Vector2( parts_[ i ].position.x - offset_x_, parts_[ i ].position.y - offset_y_ ), &parts_[ i ].trim, color );
    }
}

// �j��
void Field::destroy()
{
    // �e�N�X�`���̉��
    texture_->Release();

    // �������̊J��
    delete[] parts_;
}