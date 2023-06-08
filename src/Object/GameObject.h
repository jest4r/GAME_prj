#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "IObject.h"
#include "transform.h"
#include "SDL.h"
#include "Point.h"

struct Properties
{
    public:
        Properties(std::string textureID, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
        {
            TextureID = textureID;
            Width = width;
            Height = height;
            Flip = flip;
            X = x;
            Y = y;
        }
    public:
        int X, Y;
        int Width, Height;
        std::string TextureID;
        SDL_RendererFlip Flip;
};

class GameObject : public IObject
{
    public:
        GameObject(Properties* props): m_TextureID(props->TextureID), m_width(props->Width), m_height(props->Height), m_flip(props->Flip)
        {
            m_transform = new transform(props->X, props->Y);

            float px = props->X + props->Width/2;
            float py = props->Y + props->Height/2;
            m_origin = new Point(px, py);
        }
        inline Point* GetOrigin(){return m_origin;}
        virtual void Draw() = 0;
        virtual void Update(float dt) = 0;
        virtual void Clean() = 0;

    protected:
        Point* m_origin;
        transform* m_transform;
        int m_width, m_height;
        std::string m_TextureID;
        SDL_RendererFlip m_flip;
};

#endif // GAMEOBJECT_H
