#include "Player.h"
#include "TextureManager.h"
#include "SDL.h"

player::player(Properties* props): Character(props)
{
    m_row = 1;
    m_frameCount = 10;
    m_aniSpeed = 50;
}

void player::Draw()
{
    TextureManager::GetInstance()->DrawFrame(m_TextureID, m_transform->X, m_transform->Y, m_width, m_height, m_row, m_frame);
}


void player::Update(float dt)
{
    m_frame = (SDL_GetTicks()/m_aniSpeed) % m_frameCount;
}

void player::Clean()
{
    TextureManager::GetInstance()->Clean();
}
