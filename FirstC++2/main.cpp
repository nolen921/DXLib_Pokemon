#include<Windows.h>
#include<d3d11.h>
#include<WICTextureLoader.h>
#include<SpriteBatch.h>
#include<SimpleMath.h>
#include<CommonStates.h>
#include<ctime>
#include<cstdio>
#include"player.h"

using namespace DirectX;
using namespace SimpleMath;

// �v���g�^�C�v�錾
LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    // �����̏�����
    srand( (unsigned int)time( NULL ) );

    // �E�B���h�E�N���X�̍쐬
    WNDCLASSEX wnd;
    ZeroMemory( &wnd, sizeof( WNDCLASSEX ) );
    wnd.cbSize = sizeof( WNDCLASSEX );              // �\���̃T�C�Y
    wnd.style = CS_HREDRAW | CS_VREDRAW;           // �X�^�C��
    wnd.hInstance = hInstance;                      // �A�v���P�[�V�����C���X�^���X
    wnd.lpszClassName = "ClassName";                // �N���X��
    wnd.hCursor = LoadCursor( NULL, IDC_ARROW );    // �J�[�\���`��
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wnd.lpfnWndProc = WinProc;                      // �E�B���h�E�v���V�[�W���ւ̊֐��|�C���^

    // �o�^
    if( !RegisterClassEx( &wnd ) )
    {
        // �G���[
        return 0;
    }

    // �E�B���h�E�T�C�Y������
    RECT rect;
    rect.left = rect.top = 0L;
    rect.right = 1280L;
    rect.bottom = 720L;

    const DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    const DWORD ex_style = WS_EX_OVERLAPPEDWINDOW;
    AdjustWindowRectEx( &rect, style, false, ex_style );

    // �E�B���h�E�̍쐬
    const HWND hWnd = CreateWindowEx(
        ex_style,   // �g���E�B���h�E�X�^�C��
        "ClassName",// �N���X��
        "Title",    // �E�B���h�E�^�C�g��
        style,      // �E�B���h�E�X�^�C��
        CW_USEDEFAULT,  //�\�����WX
        CW_USEDEFAULT,  //�\�����WY
        rect.right - rect.left, // �E�B���h�E����
        rect.bottom - rect.top, // �E�B���h�E�c��
        NULL,       // �e�E�B���h�E�ւ̃n���h��
        NULL,       // ���j���[�n���h��             ���j���[�o�[������Əd���Ȃ邩��Q�[���ł͂Ȃ�ׂ����Ȃ�
        hInstance,  // �A�v���P�[�V�����C���X�^���X
        NULL        // �E�B���h�E�쐬�f�[�^
    );

    // NULL�`�F�b�N
    if( hWnd == NULL )
    {
        // �G���[
        return 0;
    }

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

    // �C���^�[�t�F�C�X�̐錾
    ID3D11Device* d3d_device;               // D3D�f�o�C�X�C���^�[�t�F�C�X
    ID3D11DeviceContext* device_context;    // �f�o�C�X�R���e�L�X�g�C���^�[�t�F�C�X
    IDXGISwapChain* swap_chain;             // �X���b�v�`�F�C���C���^�[�t�F�C�X
    D3D_FEATURE_LEVEL feature_level;        // �@�\���x��

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
        &swap_chain,                        // �X���b�v�`�F�[���C���^�[�t�F�C�X����|�C���^
        &d3d_device,                        // �̗p���ꂽ�@�\���x��
        &feature_level,                     // �f�o�C�X�R���e�L�X�g�C���^�[�t�F�C�X����|�C���^
        &device_context ) ) )
    {
        // �G���[
        return 0;
    }

    // �o�b�N�o�b�t�@�`��^�[�Q�b�g�̎擾
    ID3D11Texture2D* backbuffer = NULL;
    if( FAILED( swap_chain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(&backbuffer) ) ) )
    {
        // �G���[
        return 0;
    }

    // �`��^�[�Q�b�g�r���[�̍쐬
    ID3D11RenderTargetView* render_target_view = NULL;
    if( FAILED( d3d_device->CreateRenderTargetView(
        backbuffer,                     // �r���[�ŃA�N�Z�X���郊�\�[�X
        NULL,                           // �r���[�̒�`
        &render_target_view ) ) )
    {
        // �G���[
        return 0;
    }

    // �o�b�N�o�b�t�@�J��
    backbuffer->Release();

    // �`��^�[�Q�b�g�r���[���o�̓}�l�[�W���[�̕`��^�[�Q�b�g�Ƃ��Đݒ�
    device_context->OMSetRenderTargets(
        1,                      // �`��^�[�Q�b�g��
        &render_target_view,    // �^�[�Q�b�g�r���[�z��
        NULL );                 // �[�x/�X�e���V���r���[

    // �r���[�|�[�g�̍쐬
    D3D11_VIEWPORT vp;
    vp.Width = 1280.0F;
    vp.Height = 720.0F;
    vp.MinDepth = 0.0F;
    vp.MaxDepth = 1.0F;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    device_context->RSSetViewports( 1, &vp );

    // COM���C�u�����̏�����
    if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
    {
        // �G���[
        return 0;
    }

    // SpriteBatch�̍쐬
    SpriteBatch sprite( device_context );

    // CommonStates�̍쐬
    CommonStates state( d3d_device );

    // �E�B���h�E�̕\��
    ShowWindow( hWnd, SW_SHOWNORMAL );

    // ���C�����[�v
    MSG msg = { NULL };

    // �t�@�C�����J��
    FILE* fp = fopen( "main.txt", "r" );

    if( fp == NULL )
    {
        // �J���Ȃ�������G���[
        return 1;
    }

    // �t�@�C�����琔�l��ǂݍ���
    int num = 1000;
    fscanf( fp, "%d", &num );

    // �v���C���[�N���X
    Player* player = new Player[ num ]; /* ���[�v�ɏ����Ȃ� */

    for( int i = 0; i < num; i++ )
    {
        if( !player[ i ].init( L"kirby.png", d3d_device, device_context ) )
        {
            // �G���[
            return 0;
        }
    }

    // ���Ԍv��
    DWORD t1, t2, t3 = 0L, dt;
    t1 = timeGetTime();
    t2 = timeGetTime();

    while( msg.message != WM_QUIT )
    {
        // ���b�Z�[�W����
        if( PeekMessageA( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

        else
        {
            // �t���[�����[�g����
            t1 = timeGetTime();     // ���݂̎���
            dt = (t1 - t2) + t3;    // �O��̍X�V���獷�����v�Z

            // ��16�~���b�o�߂��Ă����珈�����s��
            if( dt > 16 )
            {
                t2 = t1;            // ���̎��Ԃ�O��̎��ԂƂ���
                t3 = dt % 16;       // �덷�����z��

                // �v���C���[�N���X�X�V
                for( int i = 0; i < num; i++ )
                    player[ i ].update();

                float color[] = { 0.1F,0.9F,0.4F,1.0F };    // RGBA��0.0�`1.0�̊ԂŐݒ�
                device_context->ClearRenderTargetView( render_target_view, color );

                // �X�v���C�g�`��J�n
                sprite.Begin( SpriteSortMode_Deferred, state.NonPremultiplied() );  /* ���̃A���t�@�錾�ɂ��A������ */

                // �v���C���[�`��
                for( int i = 0; i < num; i++ )
                    player[ i ].draw( &sprite );

                // �X�v���C�g�`��I��
                sprite.End();

                // �`��X�V
                swap_chain->Present( 1, 0 );

            }
        }
    }

    // COM���C�u�����̉��
    CoUninitialize();

    // �C���^�[�t�F�C�X�̉���i�m�ۂ������̋t�ɊJ�����Ă����j
    for( int i = 0; i < num; i++ )
        player[ i ].destroy();
    render_target_view->Release();
    swap_chain->Release();
    device_context->ClearState();
    device_context->Release();
    d3d_device->Release();

    // ���������
    delete[] player;

    return 0;
}

LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( Msg )
    {
    case WM_PAINT:
        hdc = BeginPaint( hWnd, &ps );
        EndPaint( hWnd, &ps );
        break;

    case WM_KEYDOWN:
        switch( wParam )
        {
        case VK_ESCAPE:
            // ESC�������ꂽ�烋�[�v���I������
            PostMessage( hWnd, WM_CLOSE, 0, 0 );
            break;
        }

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    }

    return DefWindowProc( hWnd, Msg, wParam, lParam );
}