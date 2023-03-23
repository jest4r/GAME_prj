#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <Animation.h>
#include "RigidBody.h"
class player: public Character
{
    public:
        player(Properties* props);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    private:
       //  int m_row, m_frame, m_frameCount;
        // int m_aniSpeed;
        Animation* m_Animation;
        RigidBody* m_RigidBody;
};

#endif
