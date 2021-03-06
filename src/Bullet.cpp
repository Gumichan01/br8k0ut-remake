
/*
*   Br8k0ut - Platform Video game
*   Copyright © 2017  Luxon Jean-Pierre
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*   Luxon Jean-Pierre (Gumichan01)
*   website: https://gumichan01.github.io/
*   mail: luxon.jean.pierre@gmail.com
*/

#include "Bullet.hpp"
#include "Game.hpp"

#include <LunatiX/LX_Texture.hpp>
#include <LunatiX/LX_Physics.hpp>
#include <LunatiX/LX_Hitbox.hpp>

using namespace LX_Physics;

namespace
{
const int OFFSET = 2;
const LX_Vector2D BULLET_V = LX_Vector2D( 0.0f, 6.6934f );
}

Bullet::Bullet( LX_Graphics::LX_Sprite * image, LX_AABB& rect )
    : graphic( image ), position( rect ), speed( BULLET_V ), y( rect.y )
{
    position.x += 1;
    position.w -= 2;
    position.h -= 2;
}


void Bullet::draw()
{
    if ( graphic != nullptr )
    {
        graphic->draw( &position );
    }
}

void Bullet::move()
{
    position.x += speed.vx;
    y += speed.vy;
    position.y = y;

    if ( position.y > Game::GAME_WIDTH )
    {
        if ( graphic != nullptr )
            graphic = nullptr;
    }
}

const LX_AABB& Bullet::getPosition() const
{
    return position;
}

