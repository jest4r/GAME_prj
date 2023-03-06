#include <SDL.h>
#include <iostream>

using namespace std;
int main(int argc, char* args[] )
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 840, 648, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 30,144,255 ,255);

    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    SDL_Delay(3000);
}
