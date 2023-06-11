#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "IObject.h"
#include "Transform.h"
#include "SDL.h"
#include "Point.h"

struct Properties {
    public:
        Properties( std::string textureid, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE ){
            X=x;
            Y=y;
            Width=width;
            Height=height;
            TextureID=textureid;
        }
    public:
        std::string TextureID;
        int Width, Height;
        float X,Y;
        SDL_RendererFlip Flip;
};

class GameObject : public IObject {
    public:
        GameObject( Properties* props ): m_TextureID(props->TextureID),
            m_Width(props->Width), m_Height(props->Height), m_Flip(props->Flip){
            m_Transform = new Transform(props->X, props->Y);
            float px = props->X + props->Width/2;
            float py = props->Y + props->Height/2;
            m_Origin = new Point( px, py );
        }

        inline Point* GetOrigin(){return m_Origin;}
        virtual void Draw()=0;
        virtual void Update( float dt )=0;
        virtual void Clean()=0;

    protected:
        Point* m_Origin;
        Transform* m_Transform;
        std::string m_TextureID;
        int m_Width, m_Height;
        SDL_RendererFlip m_Flip;

    private:
};

#endif // GAMEOBJECT_H
