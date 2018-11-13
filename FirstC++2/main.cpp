#include<Windows.h>
#include<d3d11.h>
#include<SpriteBatch.h>
#include<SimpleMath.h>
#include<CommonStates.h>

#include"direct3d.h"
#include"sprite.h"
#include"common.h"
#include"key.h"
#include"pad.h"
#include"mouse.h"

#include<cstdio>
#include<ctime>

#include "font.h"
#include "game.h"
#include "title.h"

using namespace DirectX;
using namespace SimpleMath;

// �񋓑�
enum
{
    kTitleInit,     // �^�C�g����ʏ�����
    kTitleUpdate,   // �^�C�g����ʍX�V(�`��)
    kGameInit,      // �Q�[����ʏ�����
    kGameUpdate     // �Q�[����ʍX�V(�`��)
};

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

    // Font�N���X�̏�����
    if( !Font::init() )
    {
        // �G���[
        return 0;
    }

    // �E�B���h�E�̕\��
    ShowWindow( hWnd, SW_SHOWNORMAL );

    // ���C�����[�v
    MSG msg = { NULL };

    // ���Ԍv��
    DWORD t1, t2, t3 = 0L, dt;
    t1 = timeGetTime();
    t2 = timeGetTime();

    // ���݂̍�Ɣԍ�
    int work_no = kTitleInit;
    
    Title title;
    Game game;

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

                //--------------------------------- �X�V���� --------------------------------------------

                // �L�[�{�[�h���͂̎擾
                Key::update();

                // �Q�[���p�b�h���͂̎擾
                Pad::update();

                // �}�E�X���͂̎擾
                MyMouse::update();

                // �V�[������
                switch( work_no )
                {
                case kTitleInit:
                    // �^�C�g���N���X������
                    if( !title.init() )
                    {
                        // �G���[
                        PostQuitMessage( 0 );
                    }

                    // ���̏�����
                    work_no = kTitleUpdate;
                    break;

                case kTitleUpdate:
                    // �^�C�g���N���X�X�V����
                    if( !title.update() )
                    {
                        // false���A���Ă����玟�̃V�[����
                        title.destroy();
                        work_no = kGameInit;
                    }
                    break;

                case kGameInit:
                    // �Q�[���N���X������
                    if( !game.init() )
                    {
                        // �G���[
                        PostQuitMessage( 0 );
                    }

                    // ���̏�����
                    work_no = kGameUpdate;
                    break;

                case kGameUpdate:
                    // �Q�[���N���X�X�V����
                    if( !game.update() )
                    {
                        // false���A���Ă����玟�̃V�[����
                        game.destroy();
                        work_no = kTitleInit;
                    }
                    break;

                }

                // ��ʃN���A�֐�
                Direct3D::clear();

                // �X�v���C�g�`��J�n
                Sprite::begin();

                switch( work_no )
                {
                case kTitleUpdate:
                    title.draw();
                    break;

                case kGameUpdate:
                    game.draw();
                    break;
                }

                // �X�v���C�g�`��I��
                Sprite::end();

                // �`��X�V
                Direct3D::present();
            }
        }
    }

    // COM���C�u�����̉��
    CoUninitialize();

    // �C���^�[�t�F�C�X�̉���i�m�ۂ������̋t�ɊJ�����Ă���
    title.destroy();
    game.destroy();
    Font::destroy();
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

    case WM_INPUT:
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MOUSEWHEEL:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_MOUSEHOVER:
        Keyboard::ProcessMessage( Msg, wParam, lParam );
        Mouse::ProcessMessage( Msg, wParam, lParam );
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