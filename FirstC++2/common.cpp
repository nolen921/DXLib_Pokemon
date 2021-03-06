#include "common.h"
#include "direct3d.h"

// 実体の宣言
CommonStates* Common::state_;

// 初期化
bool Common::init()
{
    // SpriteBatchクラスのメモリを確保
    state_ = new CommonStates( Direct3D::getDevice() );

    // メモリ情報チェック
    if( !state_ )
    {
        // エラー
        return false;
    }

    return true;
}