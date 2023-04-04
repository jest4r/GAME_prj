#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <Animation.h>
#include "RigidBody.h"
#include "Collider.h"
#include "vector2D.h"

#define JUMP_TIME 15.0f;
#define JUMP_FORCE 10.0f
class player: public Character
{
    public:
        player(Properties* props);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    private:
        bool m_isJumping;
        bool m_isGrounded;

        float m_jumptime;
        float m_jumpforce;


        Collider* m_collider;
        Animation* m_Animation;
        RigidBody* m_RigidBody;

        vector2D m_LastSafePosition;
};

#endif
