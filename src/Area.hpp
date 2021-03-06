
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


#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

#include "Game.hpp"

#include <LunatiX/LX_AABB.hpp>
#include <array>
#include <vector>
#include <string>

namespace LX_Graphics
{
class LX_Sprite;
class LX_StreamingTexture;
class LX_BufferedImage;
}

struct GTile
{
    unsigned int id_tile;
    unsigned int id_sprite;
    std::string type;
    LX_AABB rect;
};

struct Type
{
    unsigned id;
    std::string label;
};

class Player;

const int TILE_W = 64;
const int TILE_H = 40;

class Area
{
    friend class Player;
    unsigned int level_id;
    std::vector<Type *> vtypes;
    std::array<GTile, Game::GAME_HEIGHT * Game::GAME_WIDTH> gtiles;
    LX_Graphics::LX_StreamingTexture * map_texture;

    void parseMap( const std::string& map_string );
    void generateMap();

public:

    static const std::string TYPE_NONE;
    static const std::string TYPE_SOLID;
    static const std::string TYPE_START;
    static const std::string TYPE_DEATH;
    static const std::string TYPE_SHOT;
    static const std::string TYPE_EXIT;

    Area( unsigned int lvl );
    void draw();

    const LX_AABB getStart() const;
    void getCanons( std::vector<LX_AABB>& v );

    ~Area();
};

#endif // AREA_HPP_INCLUDED
