#include <WICTextureLoader.h>
#include "texture.h"

// �����o�ϐ��̎��̂�錾
//int Texture::num_;

ID3D11ShaderResourceView* Texture::load( const wchar_t* FileName, ID3D11Device* Device, ID3D11DeviceContext* Context )
{
    // num_ = 100;
    
    ID3D11ShaderResourceView* texture_;

    if( FAILED( CreateWICTextureFromFileEx(
        Device,                     // D3D�f�o�C�X�C���^�[�t�F�C�X
        Context,                    // �f�o�C�X�R���e�L�X�g�C���^�[�t�F�C�X
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
        return NULL;
    }

    return texture_;
}