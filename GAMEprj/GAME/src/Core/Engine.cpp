#include "Engine.h"
#include <iostream>

Engine* Engine::s_Instance = nullptr;

bool Engine::Init(){
    return m_IsRunning = true;
}

void Engine::Update(){
    std::cout << "updating.." << std::endl;
}

void Engine::Render(){

}

void Engine::Events(){

}

bool Engine::Clean(){

}

void Engine::Quit(){

}
