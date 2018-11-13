#pragma once

#include <d3d11.h>
#include "release.h"

class Title
{
private:
    ID3D11ShaderResourceView* texture_; // テクスチャ

public:
    // コンストラクタ
    Title() : texture_( NULL ) {}

    bool init();    // 初期化
    bool update();  // 更新
    void draw();    // 描画
    void destroy(); // 破棄
};

#if 0
// ゲームクラス初期化
    Game game;
    if( !game.init() )
    {
        // エラー
        return 0;
    }
// ゲームクラスアップデート
                game.update();

                // ゲームクラス描画
                game.draw();

#endif