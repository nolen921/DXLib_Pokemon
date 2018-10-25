#include "direct3d.h"

// �����o�ϐ��̎��̂�錾
ID3D11Device*           Direct3D::d3d_device_;      // D3D�f�o�C�X�C���^�[�t�F�C�X
ID3D11DeviceContext*    Direct3D::device_context_;  // �f�o�C�X�R���e�L�X�g�C���^�[�t�F�C�X
IDXGISwapChain*         Direct3D::swap_chain_;      // �X���b�v�`�F�[���C���^�[�t�F�[�X
D3D_FEATURE_LEVEL       Direct3D::feature_level_;  // �@�\���x��
ID3D11RenderTargetView* Direct3D::render_target_view_;  // �`��^�[�Q�b�g�r���[

// ������
bool Direct3D::Init( const HWND hWnd )
{
    // �@�\���x���̐ݒ�
    D3D_FEATURE_LEVEL level[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    // �X���b�v�`�F�[���̐ݒ�
    DXGI_SWAP_CHAIN_DESC sc;
    ZeroMemory( &sc, sizeof( DXGI_SWAP_CHAIN_DESC ) );                      // ������
    sc.Windowed = true;                                                     // �E�B���h�E���[�h�̐ݒ�
    sc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                               // �X���b�v�G�t�F�N�g
    sc.OutputWindow = hWnd;                                                 // �E�B���h�E�n���h���̐ݒ�
    sc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                       // �o�b�N�o�b�t�@�̎g�p���@
    sc.BufferCount = 1U;                                                    // �o�b�N�o�b�t�@�̐�
    sc.BufferDesc.Width = 1280U;                                            // �o�b�N�o�b�t�@�T�C�Y�i���j
    sc.BufferDesc.Height = 720U;                                            // �o�b�N�o�b�t�@�T�C�Y�i�c�j
    sc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                      // �o�b�N�o�b�t�@�t�H�[�}�b�g
    sc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                  //�@�X�P�[�����O���[�h
    sc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;  // �X�L�������C���`�惂�[�h
    sc.BufferDesc.RefreshRate.Numerator = 60U;                              // ���t���b�V�����[�g�i���q�j
    sc.BufferDesc.RefreshRate.Denominator = 1U;                             // ���t���b�V�����[�g(����j
    sc.SampleDesc.Count = 1;                                                // �}���`�T���v�����O�i�A���`�G�C���A�X���j
    sc.SampleDesc.Quality = 0;                                              // �}���`�T���v�����O�i��
    sc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                      // ���[�h�ݒ�

    // �e��C���^�[�t�F�C�X���쐬
    if( FAILED( D3D11CreateDeviceAndSwapChain(
        NULL,                               // DXGI�A�_�v�^�[
        D3D_DRIVER_TYPE_HARDWARE,           // �h���C�o�[�^�C�v�i_WRAP�ɂ���Ɠ������Ƃ�����j
        NULL,                               // �\�t�g�E�F�A���X�^���C�U�[DLL�n���h��
        D3D11_CREATE_DEVICE_DEBUG,          // �I�v�V�����t���O
        level,                              // �@�\���x��
        3,                                  // �@�\���x����
        D3D11_SDK_VERSION,                  // ��ɂ��̒l���w��
        &sc,                                // �X���b�v�`�F�[���\���̃|�C���^
        &swap_chain_,                        // �X���b�v�`�F�[���C���^�[�t�F�C�X����|�C���^
        &d3d_device_,                        // �̗p���ꂽ�@�\���x��
        &feature_level_,                     // �f�o�C�X�R���e�L�X�g�C���^�[�t�F�C�X����|�C���^
        &device_context_ ) ) )
    {
        // �G���[
        return false;
    }

    // �o�b�N�o�b�t�@�`��^�[�Q�b�g�̎擾
    ID3D11Texture2D* backbuffer = NULL;
    if( FAILED( swap_chain_->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(&backbuffer) ) ) )
    {
        // �G���[
        return false;
    }

    // �`��^�[�Q�b�g�r���[�̍쐬
    if( FAILED( d3d_device_->CreateRenderTargetView(
        backbuffer,                     // �r���[�ŃA�N�Z�X���郊�\�[�X
        NULL,                           // �r���[�̒�`
        &render_target_view_ ) ) )
    {
        // �G���[
        return false;
    }

    // �o�b�N�o�b�t�@�J��
    backbuffer->Release();

    // �`��^�[�Q�b�g�r���[���o�̓}�l�[�W���[�̕`��^�[�Q�b�g�Ƃ��Đݒ�
    device_context_->OMSetRenderTargets(
        1,                       // �`��^�[�Q�b�g��
        &render_target_view_,    // �^�[�Q�b�g�r���[�z��
        NULL );                  // �[�x/�X�e���V���r���[

    // �r���[�|�[�g�̍쐬
    D3D11_VIEWPORT vp;
    vp.Width = 1280.0F;
    vp.Height = 720.0F;
    vp.MinDepth = 0.0F;
    vp.MaxDepth = 1.0F;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    device_context_->RSSetViewports( 1, &vp );

    // CommonStates�̍쐬
    // CommonStates state( getDevice() );

    return true;
}

// �j���֐�
void Direct3D::destroy()
{
    // �C���^�[�t�F�C�X�̉��
    render_target_view_->Release();
    swap_chain_->Release();
    device_context_->ClearState();
    device_context_->Release();
    d3d_device_->Release();
}

// ��ʃN���A�֐�
void Direct3D::clear()
{
    float color[] = { 0.3F,0.8F,0.5F,1.0F };    // RGB��0.0�`1.0�̊ԂŐݒ�
    device_context_->ClearRenderTargetView( render_target_view_, color );
}

// ��ʍX�V�֐�
void Direct3D::present()
{
    swap_chain_->Present( 1, 0 );
}