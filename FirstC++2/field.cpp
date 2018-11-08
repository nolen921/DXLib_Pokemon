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
int Field::index_;

int Field::pokecen_width_;
int Field::pokecen_height_;
int Field::Pokecen_LayerCount_;

// �R���X�g���N�^
Field::Field()

{
    texture_ = NULL;
    parts_ = NULL;
    width_ = 0;
    height_ = 0;
    offset_x_ = 0.0F;
    offset_y_ = 0.0F;
    index_ = 0;
}

// ������
bool Field::init()
{
    // �e�N�X�`���̓ǂݍ���
    if(!(texture_ = Texture::load( L"pokemon_rse2.png" )))
    {
        // �G���[
        return false;
    }

    // �|�P�Z���e�N�X�`���̓ǂݍ���
    if( !(texture2_ = Texture::load( L"pokemon_center.png" )) )
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
            if( i <= 2 )
            {
                parts_[ j ].position.x = static_cast<float>(64.0F * (j % width_));
                parts_[ j ].position.y = static_cast<float>(64.0F * ((j % (width_ * height_)) / width_));
            }
            else
            {
                parts_[ j ].position.x = static_cast<float>(64.0F * (j % width_));
                parts_[ j ].position.y = static_cast<float>(64.0F * ((j % (width_ * height_)) / width_));
            }
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

// �l���w�肵�čX�V
void Field::set_x( const float x )
{
    offset_x_ = x;
}

void Field::set_y( const float y )
{
    offset_y_ = y;
}

// �p�[�c�ԍ����擾
int Field::getPartsId(int i)
{
    return parts_[ i ].id;
}

// �p�[�c�̕`��͈͂�ݒ�
void Field::setPartsTrim( int i, int l, int r, int t, int b )
{
    parts_[ i ].trim.left += l;
    parts_[ i ].trim.right += r;
    parts_[ i ].trim.top += t;
    parts_[ i ].trim.bottom += b;
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
    int x = static_cast<int>(offset_x_ / 64 + 10);
    int y = static_cast<int>(offset_y_ / 64 + 6);
    index_ = (y*width_) + x;

    return index_;
}

// �`��
void Field::draw( int layer )
{
    
    for( int i = width_ * height_ * layer; i < width_ * height_ * (layer + 1); i++ )
    {

        getIndex();
        XMVECTORF32 color = Colors::White;
        //if( i == index_ /*((offset_y_ / 64 + 6)* width_) + (offset_x_ / 64 + 10)*/ )
            //color = Colors::Red;

        if( layer <= 2 )
        {
            if( i % width_ <= Player::getMasuPositionX() - 11 || i % width_ >= Player::getMasuPositionX() + 10 )
            {
                continue;
            }
            if( i % (width_ * height_) / width_ <= Player::getMasuPositionY() - 7 || i % (width_ * height_) / width_ >= Player::getMasuPositionY() + 5 )
            {
                continue;
            }

            Sprite::draw( texture_, Vector2( parts_[ i ].position.x - offset_x_, parts_[ i ].position.y - offset_y_ ), &parts_[ i ].trim, color );
        }
        else
        {
            if( i % width_ <= Player::getMasuPositionX() - 11 || i % width_ >= Player::getMasuPositionX() + 10 )
            {
                continue;
            }
            if( i % (width_ * height_) / width_ <= Player::getMasuPositionY() - 7 || i % (width_ * height_) / width_ >= Player::getMasuPositionY() + 5 )
            {
                continue;
            }

            Sprite::draw( texture2_, Vector2( parts_[ i ].position.x - offset_x_, parts_[ i ].position.y - offset_y_ ), &parts_[ i ].trim, color );
        }
    }
}

// �j��
void Field::destroy()
{
    // �e�N�X�`���̉��
    texture_->Release();

    texture2_->Release();

    // �������̊J��
    delete[] parts_;
}