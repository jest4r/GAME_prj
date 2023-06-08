#include "TextureManager.h"
#include "Engine.h"
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Camera.h"
#include <tinyxml.h>
TextureManager* TextureManager::s_Instance = NULL;

bool TextureManager::Load(std::string id, std::string filename)
{
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == NULL)
    {
        SDL_Log("Error to load surface: %s, %s",filename.c_str(), SDL_GetError());
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), surface);
    if (texture == NULL)
    {
        SDL_Log("Error to get texture from surface: %s", SDL_GetError());
        return false;
    }
    m_TextureMap[id] = texture;
    return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float scaleX, float scaleY, float scrollRatio, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {0, 0, width, height};
    vector2D cam = Camera::GetInstance()->GetPosition()*scrollRatio;
    SDL_Rect destRect = {x - cam.X, y - cam.Y, width*scaleX, height*scaleY};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, NULL, flip);
}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
    SDL_Rect srcRect = {width*frame, height*(row-1), width, height};
    vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect destRect = {x - cam.X, y - cam.Y, width, height};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[id], &srcRect, &destRect, 0, NULL, flip);
}
void TextureManager::DrawTile(std::string tilesetID, int tilesize, int x, int y, int row, int frame, SDL_RendererFlip flip){
    SDL_Rect srcRect = {tilesize*frame, tilesize*row, tilesize, tilesize};

    vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect destRect = {x - cam.X, y - cam.Y, tilesize, tilesize};
    SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_TextureMap[tilesetID], &srcRect, &destRect, 0, nullptr, flip);
}
bool TextureManager::ParseTexture(std::string source){
    TiXmlDocument xml;
    xml.LoadFile (source);
    if (xml.Error())
    {
        std::cout << "Failed to load!" << source << std::endl;
        return false;
    }
    TiXmlElement* root = xml.RootElement();
    for (TiXmlElement* e=root->FirstChildElement(); e!=nullptr; e=e->NextSiblingElement()){
        if(e->Value() == std::string("texture"))
        {
            std::string id = e->Attribute("id");
            std::string src = e->Attribute("source");
            Load(id, src);
        }
    }
    return true;
}
void TextureManager::Drop(std::string id)
{
    SDL_DestroyTexture(m_TextureMap[id]);
    m_TextureMap.erase(id);
}

void TextureManager::Clean()
{
    std::map<std::string, SDL_Texture*>::iterator it;
    for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }
    m_TextureMap.clear();
    SDL_Log("Chuc ban ngu ngon");
}


