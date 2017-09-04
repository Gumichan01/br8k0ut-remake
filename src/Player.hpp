
/*
*   Br8k0ut - Platform Video game
*   Copyright © 2017 Luxon Jean-Pierre
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


#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <LunatiX/LX_AABB.hpp>
#include <LunatiX/LX_Vector2D.hpp>
#include <LunatiX/LX_Event.hpp>


namespace LX_Graphics
{
class LX_Sprite;
}

namespace LX_Physics
{
struct LX_Circle;
}


struct FloatPosition
{
    float x;
    float y;

    FloatPosition();
    FloatPosition(float fx, float fy);
    FloatPosition(const FloatPosition& fp);
    explicit FloatPosition(const LX_AABB& b);
    FloatPosition& operator =(const FloatPosition& fp);
    FloatPosition& operator =(const LX_AABB& aabb);
    FloatPosition& operator +=(const LX_Physics::LX_Vector2D& v);

    void toPixelUnit(LX_AABB& aabb);
};


class Player
{
    LX_Graphics::LX_Sprite *sprite;
    FloatPosition fpos;
    LX_AABB position;
    LX_Physics::LX_Vector2D speed;

public:

    Player(const LX_AABB& pos);

    void draw();
    void input(const LX_Event::LX_EventHandler& ev);
    void move();

    const LX_AABB& getPos();

    ~Player();
};

#endif // PLAYER_HPP_INCLUDED
