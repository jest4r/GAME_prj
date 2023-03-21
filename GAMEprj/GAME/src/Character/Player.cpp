#include "Player.h"
#include "TextureManager.h"
#include "SDL.h"

player::player(Properties* props): Character(props)
{
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 6, 80, SDL_FLIP_NONE);
}

void player::Draw()
{
    m_Animation->Draw(m_transform->X, m_transform->Y, m_width, m_height);
}


void player::Update(float dt)
{
    m_RigidBody->Update(0.4);
    m_RigidBody->ApplyForceX(5);
    m_transform->translateX(m_RigidBody->Position().X);
    m_transform->translateY(m_RigidBody->Position().Y);
    m_Animation->Update();
}

void player::Clean()
{
    TextureManager::GetInstance()->Clean();
}
