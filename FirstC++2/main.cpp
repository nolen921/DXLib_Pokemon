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

// 列挙体
enum
{
    kTitleInit,     // タイトル画面初期化
    kTitleUpdate,   // タイトル画面更新(描画)
    kGameInit,      // ゲーム画面初期化
    kGameUpdate     // ゲーム画面更新(描画)
};

// プロトタイプ宣言
LRESULT CALLBACK WinProc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    // 乱数の初期化
    srand( (unsigned int)time( NULL ) );

    // ウィンドウクラスの作成
    WNDCLASSEX wnd;
    ZeroMemory( &wnd, sizeof( WNDCLASSEX ) );
    wnd.cbSize = sizeof( WNDCLASSEX );              // 構造体サイズ
    wnd.style = CS_HREDRAW | CS_VREDRAW;           // スタイル
    wnd.hInstance = hInstance;                      // アプリケーションインスタンス
    wnd.lpszClassName = "ClassName";                // クラス名
    wnd.hCursor = LoadCursor( NULL, IDC_ARROW );    // カーソル形状
    wnd.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
    wnd.lpfnWndProc = WinProc;                      // ウィンドウプロシージャへの関数ポインタ

    // 登録
    if( !RegisterClassEx( &wnd ) )
    {
        // エラー
        return 0;
    }

    // ウィンドウサイズを決定
    RECT rect;
    rect.left = rect.top = 0L;
    rect.right = 1280L;
    rect.bottom = 720L;

    const DWORD style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;
    const DWORD ex_style = WS_EX_OVERLAPPEDWINDOW;
    AdjustWindowRectEx( &rect, style, false, ex_style );

    // ウィンドウの作成
    const HWND hWnd = CreateWindowEx(
        ex_style,   // 拡張ウィンドウスタイル
        "ClassName",// クラス名
        "Title",    // ウィンドウタイトル
        style,      // ウィンドウスタイル
        CW_USEDEFAULT,  //表示座標X
        CW_USEDEFAULT,  //表示座標Y
        rect.right - rect.left, // ウィンドウ横幅
        rect.bottom - rect.top, // ウィンドウ縦幅
        NULL,       // 親ウィンドウへのハンドル
        NULL,       // メニューハンドル             メニューバーがあると重くなるからゲームではなるべくつけない
        hInstance,  // アプリケーションインスタンス
        NULL        // ウィンドウ作成データ
    );

    // NULLチェック
    if( hWnd == NULL )
    {
        // エラー
        return 0;
    }

    // Direct3Dの初期化
    if( !Direct3D::Init( hWnd ) )
    {
        // エラー
        return 0;
    }

    // COMライブラリの初期化
    if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
    {
        // エラー
        return 0;
    }

    // Spriteクラス初期化
    if( !Sprite::init() )
    {
        // エラー
        return 0;
    }

    // Commonクラス初期化
    if( !Common::init() )
    {
        // エラー
        return 0;
    }

    // Fontクラスの初期化
    if( !Font::init() )
    {
        // エラー
        return 0;
    }

    // ウィンドウの表示
    ShowWindow( hWnd, SW_SHOWNORMAL );

    // メインループ
    MSG msg = { NULL };

    // 時間計測
    DWORD t1, t2, t3 = 0L, dt;
    t1 = timeGetTime();
    t2 = timeGetTime();

    // 現在の作業番号
    int work_no = kTitleInit;
    
    Title title;
    Game game;

    while( msg.message != WM_QUIT )
    {
        // メッセージ処理
        if( PeekMessageA( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

        else
        {
            // フレームレート制御
            t1 = timeGetTime();     // 現在の時間
            dt = (t1 - t2) + t3;    // 前回の更新から差分を計算

            // 約16ミリ秒経過していたら処理を行う
            if( dt > 16 )
            {
                t2 = t1;            // 今の時間を前回の時間とする
                t3 = dt % 16;       // 誤差分を吸収

                //--------------------------------- 更新処理 --------------------------------------------

                // キーボード入力の取得
                Key::update();

                // ゲームパッド入力の取得
                Pad::update();

                // マウス入力の取得
                MyMouse::update();

                // シーン処理
                switch( work_no )
                {
                case kTitleInit:
                    // タイトルクラス初期化
                    if( !title.init() )
                    {
                        // エラー
                        PostQuitMessage( 0 );
                    }

                    // 次の処理へ
                    work_no = kTitleUpdate;
                    break;

                case kTitleUpdate:
                    // タイトルクラス更新処理
                    if( !title.update() )
                    {
                        // falseが帰ってきたら次のシーンへ
                        title.destroy();
                        work_no = kGameInit;
                    }
                    break;

                case kGameInit:
                    // ゲームクラス初期化
                    if( !game.init() )
                    {
                        // エラー
                        PostQuitMessage( 0 );
                    }

                    // 次の処理へ
                    work_no = kGameUpdate;
                    break;

                case kGameUpdate:
                    // ゲームクラス更新処理
                    if( !game.update() )
                    {
                        // falseが帰ってきたら次のシーンへ
                        game.destroy();
                        work_no = kTitleInit;
                    }
                    break;

                }

                // 画面クリア関数
                Direct3D::clear();

                // スプライト描画開始
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

                // スプライト描画終了
                Sprite::end();

                // 描画更新
                Direct3D::present();
            }
        }
    }

    // COMライブラリの解放
    CoUninitialize();

    // インターフェイスの解放（確保した順の逆に開放していく
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
            // ESCが押されたらループを終了する
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