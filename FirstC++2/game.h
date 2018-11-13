#pragma once

// Include
#include "field.h"
#include "player.h"

// Class
class Game
{
private:
    Player player_; // プレイヤークラス     ←
    Field field_;   // フィールドクラス     ←クラス内クラス

public:
    Game();         // コンストラクタ
    ~Game();        // デストラクタ
    bool init();    // 初期化
    bool update();  // 更新
    void draw();    // 描画
    void destroy(); // 破棄
};