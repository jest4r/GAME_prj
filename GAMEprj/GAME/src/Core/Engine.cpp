#include "Engine.h"
#include "TextureManager.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector2D.h>
#include <transform.h>
#include <Player.h>
#include "Input.h"
#include "Timer.h"
#include "MapParser.h"
Engine* Engine::s_Instance = NULL;
player* player1 = NULL;
bool Engine::Init(){
    if (SDL_Init(SDL_INIT_VIDEO) !=0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
    {
        SDL_Log("Fail to initialize SDL: %s", SDL_GetError());
        return false;
    }
    SDL_WindowFlags window_flags = (SDL_WindowFlags) (SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("My lesson", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);
    if (m_Window ==  NULL)
    {
        SDL_Log("Fail to create window: %s", SDL_GetError());
        return false;
    }
    m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_Renderer == NULL)
    {
        SDL_Log("Fail to create renderer: %s", SDL_GetError());
        return false;
    }

    if (!MapParser::GetInstance()->Load()){

        std::cout<< "Failed to load map" << std::endl;
    }
    m_LevelMap = MapParser::GetInstance()->GetMap("level1");

    TextureManager::GetInstance()->Load("player", "assets/_idle.png");
    TextureManager::GetInstance()->Load("player_run", "assets/_run.png");
    player1 = new player(new Properties("player", 100, 180, 120, 120));
    transform tf;
    tf.Log();
    return m_IsRunning = true;
}

void Engine::Update(){
     //SDL_Log("Dit con me may");
     float dt = Timer::GetInstance()->GetDeltatime();
     player1->Update(dt);
     m_LevelMap->Update();
}

void Engine::Render(){
    SDL_SetRenderDrawColor(m_Renderer, 124, 218, 254, 255);
    SDL_RenderClear(m_Renderer);
    m_LevelMap->Render();
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
