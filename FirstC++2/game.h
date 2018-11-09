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
    bool init();    // 初期化
    void update();  // 更新
    void draw();    // 描画
    void destroy(); // 破棄
};