#include <WICTextureLoader.h>
#include <cstdio>
#include"direct3d.h"
#include "texture.h"
#include "error.h"

// �����o�ϐ��̎��̂�錾
//int Texture::num_;

ID3D11ShaderResourceView* Texture::load( const wchar_t* FileName )
{
    // num_ = 100;
    
    ID3D11ShaderResourceView* texture_;

    if( FAILED( CreateWICTextureFromFileEx(
        Direct3D::getDevice(),      // D3D�f�o�C�X�C���^�[�t�F�C�X
        Direct3D::getContext(),     // �f�o�C�X�R���e�L�X�g�C���^�[�t�F�C�X
        FileName,                   // �t�@�C�����i���C�h�����Ŏw��j
        0,                          // �~�j�}�b�v���x��
        D3D11_USAGE_DEFAULT,        // �g�p���@
        D3D11_BIND_SHADER_RESOURCE, // �o�C���h�̎��
        0,                          // CPU�A�N�Z�X���@
        0,                          // �t���O�I�v�V����
        WIC_LOADER_DEFAULT,         // SRGB�t���O
        NULL,                       // ���\�[�X�f�[�^����|�C���^
        &texture_ ) ) )             // �V�F�[�_�[���\�[�X�r���[
    {
        // �G���[
        // MessageBox( NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s", "Error", MB_OK | MB_ICONERROR );
        char file_name[ 256 ], str[ 256 ];
        wcstombs( file_name, FileName, 256 );
        sprintf( str, "�e�N�X�`���̓ǂݍ��݂Ɏ��s(%s)", file_name );
        Error::showDialog( str );
        return NULL;
    }

    return texture_;
}