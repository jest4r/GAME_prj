#include "Player.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
player::player(Properties* props): Character(props)
{
    m_RigidBody = new RigidBody();
    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 10, 100, SDL_FLIP_NONE);
}

void player::Draw()
{
    m_Animation->Draw(m_transform->X, m_transform->Y, m_width, m_height);
}


void player::Update(float dt)
{
    m_Animation->SetProps("player", 1, 10, 100);
    m_RigidBody->UnsetForce();
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
         {
             m_RigidBody->ApplyForceX(5*BACKWARD);
             m_Animation->SetProps("player_run", 1, 10, 100, SDL_FLIP_HORIZONTAL);
         }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
         {
             m_RigidBody->ApplyForceX(5*FORWARD);
             m_Animation->SetProps("player_run", 1, 10, 100);
         }
    /* if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
         {
             m_RigidBody->ApplyForceY(5*UPWARD);
             m_Animation->SetProps("player_run", 1, 8, 80);
         }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W))
         {
             m_RigidBody->ApplyForceY(5*DOWNWARD);
             m_Animation->SetProps("player_run", 1, 8, 80);
         }
        */
    SDL_Log("%f", dt);
    m_RigidBody->Update(dt);
    m_transform->translateX(m_RigidBody->Position().X);
   // m_transform->translateY(m_RigidBody->Position().Y);
    m_Animation->Update();
}

void player::Clean()
{
    TextureManager::GetInstance()->Clean();
}
