#include "Player.h"
#include "TextureManager.h"
#include "SDL.h"

player::player(Properties* props): Character(props)
{
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 80, SDL_FLIP_NONE);
}

void player::Draw()
{
    m_Animation->Draw(m_transform->X, m_transform->Y, m_width, m_height);
}


void player::Update(float dt)
{
    m_Animation->Update();
}

void player::Clean()
{
    TextureManager::GetInstance()->Clean();
}
