#include<Windows.h>
#include<d3d11.h>
#include<SpriteBatch.h>
#include<SimpleMath.h>
#include<CommonStates.h>
#include<Keyboard.h>

#include"player.h"
#include"direct3d.h"
#include"sprite.h"
#include"common.h"
#include"key.h"
#include"field.h"
#include"pad.h"

#include<cstdio>
#include<ctime>

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

    // Direct3D�̏�����
    if( !Direct3D::Init( hWnd ) )
    {
        // �G���[
        return 0;
    }

    // COM���C�u�����̏�����
    if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
    {
        // �G���[
        return 0;
    }

    // Sprite�N���X������
    if( !Sprite::init() )
    {
        // �G���[
        return 0;
    }

    // Common�N���X������
    if( !Common::init() )
    {
        // �G���[
        return 0;
    }

    // Keyboard�N���X������
    if( !Key::init() )
    {
        // �G���[
        return 0;
    }

    // �E�B���h�E�̕\��
    ShowWindow( hWnd, SW_SHOWNORMAL );

    // ���C�����[�v
    MSG msg = { NULL };

    int num = 1000;

    // �v���C���[�N���X
    Player player; /* ���[�v�ɏ����Ȃ� */

    if( !player.init( L"pokemon_char2.png" ) )
    {
        // �G���[
        Key::destroy();
        Common::destroy();
        Sprite::destroy();
        Direct3D::destroy();
        return 0;
    }

    // �t�B�[���h�N���X
    Field field;
    if( !field.init() )
    {
        // �G���[
        return 0;
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

                // �L�[�{�[�h���͂̎擾
                //Keyboard::State keystate = key.GetState();
                Key::update();

                Pad::update();

                // �v���C���[�N���X�X�V
                player.update( Key::getNyuryoku() );

                // ��ʃN���A�֐�
                Direct3D::clear();

                // �X�v���C�g�`��J�n
                Sprite::begin();

                // �t�B�[���h�`��1
                field.draw( 1 );

                field.draw( 0 );

                field.draw( 3 );

                // �v���C���[�`��
                player.draw();

                // �t�B�[���h�`��2
                field.draw( 2 );

                // �X�v���C�g�`��I��
                // sprite.End();
                Sprite::end();

                // �`��X�V
                Direct3D::present();
            }
        }
    }

    // COM���C�u�����̉��
    CoUninitialize();

    // �C���^�[�t�F�C�X�̉���i�m�ۂ������̋t�ɊJ�����Ă����j
    field.destroy();
    player.destroy();
    Key::destroy();
    Common::destroy();
    Sprite::destroy();
    Direct3D::destroy();

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

    case WM_ACTIVATEAPP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;

    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_KEYUP:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        break;

    case WM_KEYDOWN:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        
        switch( wParam )
        {
        case VK_ESCAPE:
            // ESC�������ꂽ�烋�[�v���I������
            PostMessage( hWnd, WM_CLOSE, 0, 0 );
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    }

    return DefWindowProc( hWnd, Msg, wParam, lParam );
}