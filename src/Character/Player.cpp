#include "Player.h"
#include "TextureManager.h"
#include "SDL.h"
#include "Input.h"
#include "Engine.h"
#include "Camera.h"
#include "CollisionHandler.h"
player::player(Properties* props): Character(props)
{
    m_isRunning = false;
    m_isAttacking = false;
    m_isCrouching = false;
    m_isFalling = false;
    m_isJumping = false;
    m_isGrounded = false;

    m_flip = SDL_FLIP_NONE;
    m_jumptime = JUMP_TIME;
    m_jumpforce = JUMP_FORCE;
    m_attacktime = ATTACK_TIME;

    m_collider = new Collider();
    m_collider->SetBuffer(-45, -50, 0, 0);

    m_RigidBody = new RigidBody();
    m_RigidBody->SetGravity(3.0f);

    m_Animation = new Animation();
    m_Animation->SetProps(m_TextureID, 1, 10, 50);
}

void player::Draw()
{
    m_Animation->Draw(m_transform->X, m_transform->Y, m_width, m_height, m_flip);

    /*vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_collider->Get();
    box.x -= cam.X;
    box.y -= cam.Y;
    SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
    */
}


void player::Update(float dt)
{
    m_isRunning = false;
    m_isCrouching = false;
    m_RigidBody->UnsetForce();

    //Run Forward
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == FORWARD && !m_isAttacking)
         {
             m_RigidBody->ApplyForceX(RUN_FORCE*FORWARD);
             m_flip = SDL_FLIP_NONE;
             m_isRunning = true;
         }
    //Run backward
    if (Input::GetInstance()->GetAxisKey(HORIZONTAL) == BACKWARD && !m_isAttacking)
         {
             m_RigidBody->ApplyForceX(RUN_FORCE*BACKWARD);
             m_flip = SDL_FLIP_HORIZONTAL;
             m_isRunning = true;
         }
    // Crouch
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S))
    {
       m_RigidBody->UnsetForce();
        m_isCrouching = true;
    }
    //Attack
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
    {
        m_RigidBody->UnsetForce();
        m_isAttacking = true;
    }
    //Jump
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_isGrounded)
    {
        m_isJumping = true;
        m_isGrounded = false;
        m_RigidBody->ApplyForceY(m_jumpforce*UPWARD);
    }
    if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) && m_isJumping && m_jumptime > 0)
    {
        m_jumptime -= dt;
        m_RigidBody->ApplyForceY(m_jumpforce*UPWARD);
    }
    else{
        m_isJumping = false;
        m_jumptime = JUMP_TIME;
    }
    //Fall
    if (m_RigidBody->Velocity().Y > 0 && !m_isGrounded)
        m_isFalling = true;
    else
        m_isFalling = false;
    //Attack timer
    if (m_isAttacking && m_attacktime > 0)
    {
        m_attacktime -= dt;
    }
    else {
        m_isAttacking = false;
        m_attacktime = ATTACK_TIME;
    }

    //move on X axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.X = m_transform->X;
    m_transform->X += m_RigidBody->Position().X;
    m_collider->Set(m_transform->X, m_transform->Y, 18, 50);

    if (CollisionHandler::GetInstance()->MapCollision(m_collider->Get()))
        m_transform->X = m_LastSafePosition.X;


    //move on Y axis
    m_RigidBody->Update(dt);
    m_LastSafePosition.Y = m_transform->Y;
    m_transform->Y += m_RigidBody->Position().Y;
    m_collider->Set(m_transform->X, m_transform->Y, 18, 50);

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
    AnimationState();
    m_Animation->Update();
}

void player::AnimationState(){
    m_Animation->SetProps("player_idle",1 , 10, 50);
    if (m_isRunning) m_Animation->SetProps("player_run", 1, 10, 50);
    if (m_isCrouching) m_Animation->SetProps("player_crouch",1, 1, 50);
    if (m_isJumping) m_Animation->SetProps("player_jump",1, 3, 50);
    if (m_isFalling) m_Animation->SetProps("player_fall",1, 1, 50);
    if (m_isAttacking) m_Animation->SetProps("player_attack",1, 10, 50);

}
void player::Clean()
{
    TextureManager::GetInstance()->Drop(m_TextureID);
}
