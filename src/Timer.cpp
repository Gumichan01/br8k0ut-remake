
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


#include "Timer.hpp"
#include <LunatiX/LX_Timer.hpp>

void Timer::start()
{
    if ( m_stopped )
    {
        m_start = LX_Timer::getTicks();
        m_stopped = false;
    }
}

void Timer::pause()
{
    if ( !m_stopped && !m_paused )
    {
        m_pause = getTicks() - m_start - m_tradeoff;
        m_paused = true;
    }
}


void Timer::resume()
{
    if ( !m_stopped && m_paused )
    {
        m_tradeoff += getTicks() - m_pause;
        m_paused = false;
    }
}

unsigned int Timer::lap()
{
    unsigned int t = Timer::getTicks();
    stop();
    reset();
    start();
    return t;
}

unsigned int Timer::getTicks()
{
    if ( m_stopped || m_paused )
        return m_pause - m_start - m_tradeoff;

    return LX_Timer::getTicks() - m_tradeoff;
}

void Timer::stop()
{
    pause();
    m_stopped = true;
    m_paused = false;
}

void Timer::reset()
{
    m_start = 0UL;
    m_pause = 0UL;
    m_tradeoff = 0UL;
    m_stopped = true;
    m_paused = false;
}
