#include "Player.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "Camera.h"
#include "CollisionHandler.h"
player::player(Properties* props): Character(props)
{
    m_jumptime = JUMP_TIME;
    m_jumpforce = JUMP_FORCE;

    m_collider = new Collider();
    m_collider->SetBuffer(0, -25, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 10, 50, SDL_FLIP_NONE);
}

void player::Draw()
{
    m_Animation->Draw(m_transform->X, m_transform->Y, m_width, m_height);

    vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}


void player::Update(float dt)
{
    m_Animation->SetProps("player", 1, 10, 50);
    m_RigidBody->UnsetForce();

    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
         {
             m_RigidBody->ApplyForceX(5*BACKWARD);
             m_Animation->SetProps("player_run", 1, 10, 50, SDL_FLIP_HORIZONTAL);
         }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D))
         {
             m_RigidBody->ApplyForceX(5*FORWARD);
             m_Animation->SetProps("player_run", 1, 10, 50);
         }
    // Jump
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_isGrounded)
    {
        m_isJumping = true;
        m_isGrounded = false;
        m_RigidBody->ApplyForceY(UPWARD*m_jumpforce);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_isJumping && m_jumptime > 0)
    {
        m_jumptime -= dt;
        m_RigidBody->ApplyForceY(UPWARD*m_jumpforce);
    }
    else
    {
        m_isJumping = false;
        m_jumptime = JUMP_TIME;
    }

    //move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_transform->X;
    m_transform->X += m_RigidBody->Position().X;
    m_collider->Set(m_transform->X, m_transform->Y, 96, 96);
    if (CollisionHandler::GetInstance()->MapCollision(m_collider->Get()))
        m_transform->X = m_LastSafePosition.X;


    //move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_transform->Y;
    m_transform->Y += m_RigidBody->Position().Y;
    m_collider->Set(m_transform->X, m_transform->Y, 96, 96);

    if (CollisionHandler::GetInstance()->MapCollision(m_collider->Get()))
    {
        m_isGrounded = true;
        m_transform->Y = m_LastSafePosition.Y;
    }
    else{
        m_isGrounded = false;
    }
    m_origin->X = m_transform->X + m_width/2;
    m_origin->Y = m_transform->Y + m_height/2;
    m_Animation->Update();
}

void player::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}
