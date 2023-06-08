#include "Camera.h"

Camera* Camera::s_Instance = NULL;
void Camera::Update(float dt)
{
    if (m_target != nullptr)
    {
        m_viewbox.x = m_target->X - SCREEN_WIDTH / 2;
        m_viewbox.y = m_target->Y - SCREEN_HEIGHT / 2;

        if (m_viewbox.x < 0){
            m_viewbox.x = 0;
        }
         if (m_viewbox.y < 0){
            m_viewbox.y = 0;
        }

        if (m_viewbox.x > (2*SCREEN_WIDTH - m_viewbox.w)){
            m_viewbox.x = (2*SCREEN_WIDTH - m_viewbox.w);
        }
        if (m_viewbox.y > (SCREEN_HEIGHT - m_viewbox.h)){
            m_viewbox.y = (SCREEN_HEIGHT - m_viewbox.h);
        }
        m_position = vector2D(m_viewbox.x, m_viewbox.y);
    }
}
