#include "Engine.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector2D.h>
#include <transform.h>
#include <Player.h>
#include "Input.h"
Engine* Engine::s_Instance = NULL;
player* player1 = NULL;
bool Engine::Init(){
    if (SDL_Init(SDL_INIT_VIDEO) !=0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Fail to initialize SDL: %s", SDL_GetError());
        return false;
    }

    m_Window = SDL_CreateWindow("My lesson", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_HEIGHT, SCREEN_HEIGHT, 0);
    if (m_Window ==  NULL)
    {
        SDL_Log("Fail to create window: %s", SDL_GetError());
    }
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == NULL)
    {
        SDL_Log("Fail to create renderer: %s", SDL_GetError());
    }
    TextureManager::GetInstance()->Load("player", "assets/check.png");
    player1 = new player(new Properties("player", 100, 200, 48, 86));
    transform tf;
    tf.Log();
    return m_IsRunning = true;
}

void Engine::Update(){
     //SDL_Log("Dit con me may");
     if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_UP))
         {
             SDL_Log("Key up pushed");
         }
     player1->Update(0);
}

void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);
    player1->Draw();
    SDL_RenderPresent(m_Renderer);
}

void Engine::Events(){
    Input::GetInstance()->Listen();
}

bool Engine::Clean(){
    TextureManager::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}

void Engine::Quit(){
    m_IsRunning = false;
}
