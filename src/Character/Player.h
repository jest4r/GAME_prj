#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <Animation.h>
#include "RigidBody.h"
#include "Collider.h"
#include "vector2D.h"

#define JUMP_TIME 15.0f;
#define JUMP_FORCE 10.0f

#define RUN_FORCE  4.0f
#define ATTACK_TIME 20.0f
class player: public Character
{
    public:
        player(Properties* props);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);
    private:
        void AnimationState();

    private:
        bool m_isJumping;
        bool m_isGrounded;
        bool m_isFalling;
        bool m_isRunning;
        bool m_isAttacking;
        bool m_isCrouching;

        float m_jumptime;
        float m_jumpforce;
        float m_attacktime;


        Collider* m_collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
        SDL_RendererFlip m_flip;

        vector2D m_LastSafePosition;
};

#endif
