#include "game.h"
#include "key.h"

// ������
bool Game::init()
{
    // �����o������
    if( !field_.init() ) return false;
    if( !player_.init( L"pokemon_char2.png" ) )  return false;

    return true;
}

// �X�V
void Game::update()
{
    player_.update();
}

// �`��
void Game::draw()
{
    // �t�B�[���h�`��1
    field_.draw( 1, false );

    field_.draw( 0, false );

    field_.draw( 3, false );

    // �v���C���[�`��
    player_.draw();

    // �t�B�[���h�`��2
    field_.draw( 2, false );

    field_.draw( 0, true );
}

// �j��
void Game::destroy()
{
    field_.destroy();
    player_.destroy();
}