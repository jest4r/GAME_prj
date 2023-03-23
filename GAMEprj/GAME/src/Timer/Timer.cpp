#include "Timer.h"
#include <SDL.h>
Timer* Timer::s_Instance = nullptr;
void Timer::Tick()
{
    m_deltatime = (SDL_GetTicks() - m_lasttime)*(TARGET_FPS/1000.0f);

    if (m_deltatime > TARGET_DELTATIME)
        m_deltatime = TARGET_DELTATIME;
    m_lasttime = SDL_GetTicks();
}
