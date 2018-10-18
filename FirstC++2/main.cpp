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

    // 機能レベルの設定
    D3D_FEATURE_LEVEL level[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    // スワップチェーンの設定
    DXGI_SWAP_CHAIN_DESC sc;
    ZeroMemory( &sc, sizeof( DXGI_SWAP_CHAIN_DESC ) );                      // 初期化
    sc.Windowed = true;                                                     // ウィンドウモードの設定
    sc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;                               // スワップエフェクト
    sc.OutputWindow = hWnd;                                                 // ウィンドウハンドルの設定
    sc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;                       // バックバッファの使用方法
    sc.BufferCount = 1U;                                                    // バックバッファの数
    sc.BufferDesc.Width = 1280U;                                            // バックバッファサイズ（横）
    sc.BufferDesc.Height = 720U;                                            // バックバッファサイズ（縦）
    sc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;                      // バックバッファフォーマット
    sc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;                  //　スケーリングモード
    sc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;  // スキャンライン描画モード
    sc.BufferDesc.RefreshRate.Numerator = 60U;                              // リフレッシュレート（分子）
    sc.BufferDesc.RefreshRate.Denominator = 1U;                             // リフレッシュレート(分母）
    sc.SampleDesc.Count = 1;                                                // マルチサンプリング（アンチエイリアス数）
    sc.SampleDesc.Quality = 0;                                              // マルチサンプリング品質
    sc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;                      // モード設定

    // インターフェイスの宣言
    ID3D11Device* d3d_device;               // D3Dデバイスインターフェイス
    ID3D11DeviceContext* device_context;    // デバイスコンテキストインターフェイス
    IDXGISwapChain* swap_chain;             // スワップチェインインターフェイス
    D3D_FEATURE_LEVEL feature_level;        // 機能レベル

    // 各種インターフェイスを作成
    if( FAILED( D3D11CreateDeviceAndSwapChain(
        NULL,                               // DXGIアダプター
        D3D_DRIVER_TYPE_HARDWARE,           // ドライバータイプ（_WRAPにすると動くことがある）
        NULL,                               // ソフトウェアラスタライザーDLLハンドル
        D3D11_CREATE_DEVICE_DEBUG,          // オプションフラグ
        level,                              // 機能レベル
        3,                                  // 機能レベル個数
        D3D11_SDK_VERSION,                  // 常にこの値を指定
        &sc,                                // スワップチェーン構造体ポインタ
        &swap_chain,                        // スワップチェーンインターフェイス受取先ポインタ
        &d3d_device,                        // 採用された機能レベル
        &feature_level,                     // デバイスコンテキストインターフェイス受取先ポインタ
        &device_context ) ) )
    {
        // エラー
        return 0;
    }

    // バックバッファ描画ターゲットの取得
    ID3D11Texture2D* backbuffer = NULL;
    if( FAILED( swap_chain->GetBuffer(
        0,
        __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(&backbuffer) ) ) )
    {
        // エラー
        return 0;
    }

    // 描画ターゲットビューの作成
    ID3D11RenderTargetView* render_target_view = NULL;
    if( FAILED( d3d_device->CreateRenderTargetView(
        backbuffer,                     // ビューでアクセスするリソース
        NULL,                           // ビューの定義
        &render_target_view ) ) )
    {
        // エラー
        return 0;
    }

    // バックバッファ開放
    backbuffer->Release();

    // 描画ターゲットビューを出力マネージャーの描画ターゲットとして設定
    device_context->OMSetRenderTargets(
        1,                      // 描画ターゲット数
        &render_target_view,    // ターゲットビュー配列
        NULL );                 // 深度/ステンシルビュー

    // ビューポートの作成
    D3D11_VIEWPORT vp;
    vp.Width = 1280.0F;
    vp.Height = 720.0F;
    vp.MinDepth = 0.0F;
    vp.MaxDepth = 1.0F;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    device_context->RSSetViewports( 1, &vp );

    // COMライブラリの初期化
    if( FAILED( CoInitializeEx( NULL, COINIT_MULTITHREADED ) ) )
    {
        // エラー
        return 0;
    }

    // SpriteBatchの作成
    SpriteBatch sprite( device_context );

    // CommonStatesの作成
    CommonStates state( d3d_device );

    // ウィンドウの表示
    ShowWindow( hWnd, SW_SHOWNORMAL );

    // メインループ
    MSG msg = { NULL };

    // ファイルを開く
    FILE* fp = fopen( "main.txt", "r" );

    if( fp == NULL )
    {
        // 開けなかったらエラー
        return 1;
    }

    // ファイルから数値を読み込む
    int num = 1000;
    fscanf( fp, "%d", &num );

    // プレイヤークラス
    Player* player = new Player[ num ]; /* ループに書かない */

    for( int i = 0; i < num; i++ )
    {
        if( !player[ i ].init( L"kirby.png", d3d_device, device_context ) )
        {
            // エラー
            return 0;
        }
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

                // プレイヤークラス更新
                for( int i = 0; i < num; i++ )
                    player[ i ].update();

                float color[] = { 0.1F,0.9F,0.4F,1.0F };    // RGBAを0.0～1.0の間で設定
                device_context->ClearRenderTargetView( render_target_view, color );

                // スプライト描画開始
                sprite.Begin( SpriteSortMode_Deferred, state.NonPremultiplied() );  /* 中のアルファ宣言により、透明化 */

                // プレイヤー描画
                for( int i = 0; i < num; i++ )
                    player[ i ].draw( &sprite );

                // スプライト描画終了
                sprite.End();

                // 描画更新
                swap_chain->Present( 1, 0 );

            }
        }
    }

    // COMライブラリの解放
    CoUninitialize();

    // インターフェイスの解放（確保した順の逆に開放していく）
    for( int i = 0; i < num; i++ )
        player[ i ].destroy();
    render_target_view->Release();
    swap_chain->Release();
    device_context->ClearState();
    device_context->Release();
    d3d_device->Release();

    // メモリ解放
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
            // ESCが押されたらループを終了する
            PostMessage( hWnd, WM_CLOSE, 0, 0 );
            break;
        }

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    }

    return DefWindowProc( hWnd, Msg, wParam, lParam );
}