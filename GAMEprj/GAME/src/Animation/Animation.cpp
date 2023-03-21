#include "Animation.h"
#include "TextureManager.h"

void Animation::Update()
{
    m_spriteFrame = (SDL_GetTicks()/m_aniSpeed) % m_frameCount;
}

void Animation::Draw(float x, float y, int spriteWidth, int spriteHeight)
{
    TextureManager::GetInstance()->DrawFrame(m_textureID, x, y ,spriteWidth, spriteHeight, m_spriteRow, m_spriteFrame, m_flip);
}

void Animation::SetProps(std::string textureID, int spriteRow, int frameCount, int aniSpeed, SDL_RendererFlip flip)
{
    m_textureID = textureID;
    m_spriteRow = spriteRow;
    m_frameCount = frameCount;
    m_aniSpeed = aniSpeed;
    m_flip = flip;
}
