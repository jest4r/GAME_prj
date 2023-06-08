#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "vector2D.h"
#define UNIT_MASS 1.0f
#define GRAVITY 9.8f

#define FORWARD 1
#define BACKWARD -1
#define UPWARD -1
#define DOWNWARD 1
class RigidBody
{
    public:
        RigidBody() {
            m_mass = UNIT_MASS;
            m_gravity = GRAVITY;
        }
        //Setter Gravity & mass
        inline void SetMass(float mass) {m_mass = mass;}
        inline void SetGravity(float gravity) {m_gravity = gravity;}

        //Force
        inline void ApplyForce(vector2D F){m_force = F;}
        inline void ApplyForceX(float Fx) {m_force.X = Fx;}
        inline void ApplyForceY(float Fy) {m_force.Y = Fy;}
        inline void UnsetForce(){m_force = vector2D(0,0);}

        //Friction
        inline void ApplyFriction(vector2D Fr) {m_friction = Fr;}
        inline void UnsetFriction() {m_friction = vector2D(0,0);}

        //Getters
        inline float GetMass() {return m_mass;}
        inline vector2D Position() {return m_position;}
        inline vector2D Velocity() {return m_velocity;}
        inline vector2D Accelaration() {return m_accelaration;}
        // update method
        void Update(float dt)
        {
            m_accelaration.X = (m_force.X + m_friction.X)/m_mass;
            //m_accelaration.Y = (m_force.Y + m_friction.Y)/m_mass;
            m_accelaration.Y = (m_gravity + m_force.Y)/m_mass;
            m_velocity = m_accelaration;
            m_position = m_velocity;
        }
    private:
        float m_mass;
        float m_gravity;
        vector2D m_force;
        vector2D m_friction;
        vector2D m_position;
        vector2D m_velocity;
        vector2D m_accelaration;
};

#endif // RIGIDBODY_H
