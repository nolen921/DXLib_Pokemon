#include "collision.h"
#include "player.h"
#include "field.h"

void Collision::collision( int direction )
{
    for( int i = 0; i < Field::getLayer(); i++ )
    {
        switch( direction )
        {
        case 0:
            if( Field::getPartsId( Player::getMasuPositionY() * Field::getMapWidth() + Player::getMasuPositionX() + Field::getMapWidth() ) >= 128 % 10000 && Field::getPartsId( Player::getMasuPositionY() * Field::getMapWidth() + Player::getMasuPositionX() + Field::getMapWidth() ) <= 130 % 10000 )
            {
                Player::setCollision( false );
                Player::setMasuPositionY( Player::getMasuPositionY() + 2 );
                Player::setJumpSwitch( 1 );
            }
            else if( (Field::getPartsId( Player::getMasuPositionY() * Field::getMapWidth() + Player::getMasuPositionX() + Field::getMapWidth() ) <= 63 % 10000 || Field::getPartsId( Player::getMasuPositionY() * Field::getMapWidth() + Player::getMasuPositionX() + Field::getMapWidth() ) >= 230 % 10000 ))
            {
                Player::setCollision( false );
                Player::setMasuPositionY( Player::getMasuPositionY() + 1 );
                Player::setMove( true );
            }
            else
            {
                Player::setCollision( true );
                Player::animation();
            }
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        }
    }
}