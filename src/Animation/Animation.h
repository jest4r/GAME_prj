#ifndef ANIMATION_H
#define ANIMATION_H
#include <string>
#include <SDL.h>

class Animation
{
    public:
        Animation(){}
        void Update();
        void Draw(float x, float y, int spriteWidth, int spriteHeight);
        void SetProps(std::string textureID, int spriteRow, int frameCount, int aniSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

    protected:

    private:
        int m_spriteRow, m_spriteFrame;
        int m_aniSpeed, m_frameCount;
        std::string m_textureID;
        SDL_RendererFlip m_flip;
};

#endif // ANIMATION_H
