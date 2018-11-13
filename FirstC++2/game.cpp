#include "game.h"
#include "key.h"

// コンストラクタ
Game::Game()
{

}

// デストラクタ
Game::~Game()
{

}

// 初期化
bool Game::init()
{
    // メンバ初期化
    if( !field_.init() ) return false;
    if( !player_.init( L"pokemon_char2.png" ) )  return false;

    return true;
}

// 更新
bool Game::update()
{
    const Keyboard::State key = Key::getState();

    // Tが押されたらタイトル画面に戻る
    if( key.T )
    {
        return false;
    }


    player_.update();

    return true;
}

// 描画
void Game::draw()
{
    // フィールド描画1
    field_.draw( 1, false );

    field_.draw( 0, false );

    field_.draw( 3, false );

    // プレイヤー描画
    player_.draw();

    // フィールド描画2
    field_.draw( 2, false );

    field_.draw( 0, true );
}

// 破棄
void Game::destroy()
{
    field_.destroy();
    player_.destroy();
}