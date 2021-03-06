
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

#include "Game.hpp"
#include "Area.hpp"
#include "Player.hpp"
#include "Shooter.hpp"
#include "Bullet.hpp"
#include "Framerate.hpp"

#include <LunatiX/LX_Window.hpp>
#include <LunatiX/LX_Texture.hpp>
#include <LunatiX/LX_Timer.hpp>
#include <LunatiX/LX_Mixer.hpp>
#include <LunatiX/LX_Music.hpp>
#include <LunatiX/LX_Log.hpp>
#include <sstream>

namespace
{
const std::string MUSIC_PATH( "data/audio/gumichan01-eastern_wind.ogg" );
const std::string BULLET_PATH( "data/image/bullet.png" );
const std::string FONT_FILE( "font/Prototype.ttf" );
const LX_Colour BLACK_COLOUR = {0, 0, 0, 0};
const unsigned int TEXT_SIZE = 64U;
const unsigned short VOLUME = 75;
LX_Graphics::LX_Sprite * bullet_sp = nullptr;

inline const char * sec_( int second )
{
    return second < 10 ? "0" : "";
}

inline const char * minute_( int minute )
{
    return minute < 10 ? "0" : "";
}

const std::string toString( unsigned int t )
{
    std::ostringstream ss;
    const unsigned int H_MINUTE = 60U;
    const unsigned int M_SECOND = 60U;
    const unsigned int D = t / 1000U;
    const unsigned int MI = t - D * 1000U;
    unsigned int hour, minute, second;

    hour   = 0U;
    minute = 0U;
    second = 0U;

    if ( D > M_SECOND )
    {
        minute = D / M_SECOND;
        second = D % M_SECOND;

        if ( minute > H_MINUTE )
        {
            hour = minute / H_MINUTE;
            minute = minute % H_MINUTE;
        }
    }
    else
        second = D;

    if ( hour > 0 )
        ss << hour << ":" << minute_( minute ) << minute << ":" << sec_( second ) << second;
    else if ( minute > 0 )
        ss << minute << ":" << sec_( second ) << second;
    else
        ss << second << "." << MI;

    return ss.str();
}

}

using namespace LX_Event;


Game::Game( LX_Win::LX_Window& w ) : done( false ), lvl_count( 0 ),
    exit_status( false ), player( nullptr ), win( w ), music( nullptr ), ev(),
    total_time( 0U ), font( FONT_FILE, BLACK_COLOUR, TEXT_SIZE ),
    time_texture( nullptr ), timer()
{
    LX_Mixer::setOverallVolume( VOLUME );
    music = new LX_Mixer::LX_Music( MUSIC_PATH );
    bullet_sp = new LX_Graphics::LX_Sprite( BULLET_PATH, win );
    time_texture = new LX_Graphics::LX_BlendedTextTexture( font, win );
}


void Game::play()
{
    music->play( -1 );
    timer.start();
    timer.pause();
    while ( lvl_count < NB_LEVELS && !exit_status )
    {
        area = new Area( lvl_count + 1 );
        player = new Player( area->getStart(), *area );
        loop();

        delete area;
        delete player;
        area = nullptr;
        player = nullptr;
        lvl_count++;
    }

    timer.stop();
    music->stop();
    music->close();
}


void Game::loadShooters()
{
    std::vector<LX_AABB> boxes;
    area->getCanons( boxes );

    for ( const LX_AABB& b : boxes )
    {
        shooters.push_back( new Shooter( *this, b ) );
    }
}

void Game::loop()
{
    done = false;
    loadShooters();
    timer.resume();

    if ( lvl_count == NB_LEVELS - 1 )
    {
        std::ostringstream os;
        os << "Done in " << toString( total_time );
        time_texture->setText( os.str() );
        time_texture->setPosition( 512, 32 );
    }

    while ( !done )
    {
        if ( ( done = input() ) == true )
            continue;

        status();
        physics();
        display();
        Framerate::regulate();
        Framerate::cycle();
    }

    timer.pause();

    if ( lvl_count == NB_LEVELS - 2 )
        total_time = timer.getTicks();

    clean();
}


bool Game::input()
{
    static bool full = false;
    bool _done = false;

    while ( ev.pollEvent() )
    {
        switch ( ev.getEventType() )
        {
        case LX_EventType::LX_QUIT:
            _done = true;
            exit_status = true;
            break;

        case LX_EventType::LX_KEYUP:
            if ( ev.getKeyCode() == SDLK_f )
            {
                win.toggleFullscreen( full ? LX_Win::LX_WINDOW_NO_FULLSCREEN : LX_Win::LX_WINDOW_FULLSCREEN );
                full = !full;
            }
            else if ( ev.getKeyCode() == SDLK_ESCAPE )
            {
                _done = true;
                exit_status = true;
            }
            else
                player->input( ev );
            break;

        default:
            break;
        }
    }

    player->inputState();

    return _done;
}



void Game::physics()
{
    done = player->status( bullets );
}


void Game::status()
{
    player->move();

    for ( Shooter * shooter : shooters )
        shooter->strategy();

    for ( size_t i = 0; i < bullets.size(); ++i )
    {
        const LX_AABB& pos = bullets[i]->getPosition();

        if ( pos.y > GAME_HEIGHT )
        {
            delete bullets[i];
            bullets.erase( bullets.begin() + i );
            i--;
            continue;
        }

        bullets[i]->move();
    }
}

void Game::clean()
{
    for ( size_t i = 0; i < shooters.size(); ++i )
    {
        delete shooters[i];
    }

    for ( size_t j = 0; j < bullets.size(); ++j )
    {
        delete bullets[j];
    }

    shooters.clear();
    bullets.clear();
}

void Game::display()
{
    win.clearWindow();
    area->draw();

    for ( Bullet * bullet : bullets )
        bullet->draw();

    player->draw();

    if ( lvl_count == NB_LEVELS - 1 )
        time_texture->draw();

    win.update();
}


void Game::acceptBullet( LX_AABB& bullet_rect )
{
    bullets.push_back( new Bullet( bullet_sp, bullet_rect ) );
}

Game::~Game()
{
    delete time_texture;
    delete area;
    delete player;
    delete music;
    delete bullet_sp;
}
