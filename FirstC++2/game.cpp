#include "game.h"
#include "key.h"

// �R���X�g���N�^
Game::Game()
{

}

// �f�X�g���N�^
Game::~Game()
{

}

// ������
bool Game::init()
{
    // �����o������
    if( !field_.init() ) return false;
    if( !player_.init( L"pokemon_char2.png" ) )  return false;

    return true;
}

// �X�V
bool Game::update()
{
    const Keyboard::State key = Key::getState();

    // T�������ꂽ��^�C�g����ʂɖ߂�
    if( key.T )
    {
        return false;
    }


    player_.update();

    return true;
}

// �`��
void Game::draw()
{
    // �t�B�[���h�`��1
    field_.draw( 1, false );

    field_.draw( 0, false );

    field_.draw( 3, false );

    field_.draw( 4, false );

    // �v���C���[�`��
    player_.draw();

    // �t�B�[���h�`��2
    field_.draw( 2, false );
}

// �j��
void Game::destroy()
{
    field_.destroy();
    player_.destroy();
}