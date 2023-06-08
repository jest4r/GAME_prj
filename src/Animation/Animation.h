#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <SDL.h>

class Animation
{
    public:
        Animation(){}
        void Update();
        void Draw(float x, float y, int spriteWidth, int spriteHeight, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int aniSpeed);

    protected:

    private:
        int m_spriteRow, m_spriteFrame;
        int m_aniSpeed, m_frameCount;
        std::string m_textureID;
};

#endif // ANIMATION_H
