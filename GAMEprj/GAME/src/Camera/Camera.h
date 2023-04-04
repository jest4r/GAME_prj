#ifndef CAMERA_H
#define CAMERA_H
#include "SDL.h"
#include "Point.h"
#include "vector2D.h"
#include "Engine.h"
class Camera
{
    public:
        void Update(float dt);
        inline static Camera* GetInstance() {return s_Instance = (s_Instance != NULL)? s_Instance : new Camera();}
        inline SDL_Rect GetViewBox() {return m_viewbox;}
        inline vector2D GetPosition() {return m_position;}
        inline void SetTarget (Point* target){m_target = target;}

    private:
        Camera() {m_viewbox = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};}
        SDL_Rect m_viewbox;

        Point* m_target;
        vector2D m_position;
        static Camera* s_Instance;
};

#endif // CAMERA_H
