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

    // Keyboardクラス初期化
    if( !Key::init() )
    {
        // エラー
        return 0;
    }

    // ウィンドウの表示
    ShowWindow( hWnd, SW_SHOWNORMAL );

    // メインループ
    MSG msg = { NULL };

    int num = 1000;

    // プレイヤークラス
    Player player; /* ループに書かない */

    if( !player.init( L"pokemon_char2.png" ) )
    {
        // エラー
        Key::destroy();
        Common::destroy();
        Sprite::destroy();
        Direct3D::destroy();
        return 0;
    }

    // フィールドクラス
    Field field;
    if( !field.init() )
    {
        // エラー
        return 0;
    }

    // 時間計測
    DWORD t1, t2, t3 = 0L, dt;
    t1 = timeGetTime();
    t2 = timeGetTime();

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

                // キーボード入力の取得
                //Keyboard::State keystate = key.GetState();
                Key::update();

                Pad::update();

                // プレイヤークラス更新
                player.update( Key::getNyuryoku() );

                // 画面クリア関数
                Direct3D::clear();

                // スプライト描画開始
                Sprite::begin();

                // フィールド描画1
                field.draw( 1 );

                field.draw( 0 );

                field.draw( 3 );

                // プレイヤー描画
                player.draw();

                // フィールド描画2
                field.draw( 2 );

                // スプライト描画終了
                // sprite.End();
                Sprite::end();

                // 描画更新
                Direct3D::present();
            }
        }
    }

    // COMライブラリの解放
    CoUninitialize();

    // インターフェイスの解放（確保した順の逆に開放していく）
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