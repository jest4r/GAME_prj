#include "Menu.h"
#include "Input.h"
#include "Play.h"
#include "Engine.h"
#include "Texture.h"
#include "Button.h"
#include "Timer.h"
#include "Sound.h"

Menu *Menu::s_Instance = nullptr;
Button *play = nullptr;
Button *quit = nullptr;
Button *ranking = nullptr;
Button *howto = nullptr;
void Menu::Init()
{
    SDL_Log("Mode: Menu");
    Sound::GetInstance()->LoadMusic("MenuSound", "assets/sounds/menu.wav");
    Texture::GetInstance()->Load("MenuBg", "assets/backgrounds/bg.png");
    Texture::GetInstance()->Load("PlayBt", "assets/interface/pixelButton.png");
    play = new Button(new Properties("PlayBt", 270, 480, 192, 192), 6, 0, 0.5);
    quit = new Button(new Properties("PlayBt", 470, 480, 192, 192), 1, 0, 0.5);
    ranking = new Button (new Properties("PlayBt", 370, 480, 192, 192), 0, 0, 0.5);
    howto = new Button (new Properties("PlayBt", 570, 480, 192, 192), 3, 1, 0.5);

    Sound::GetInstance()->PlayMusic("MenuSound");
}

void Menu::Update()
{
    float dt = Timer::GetInstance()->GetDeltaTime();

    play->Update(dt);
    quit->Update(dt);
    ranking->Update(dt);
    howto->Update(dt);
}

void Menu::Render()
{
    Texture::GetInstance()->Draw("MenuBg", 0, 0, 960, 700);
    Texture::GetInstance()->DrawText("Game", "A Game made by Jest4r", 350, 40, 0.5);
    play->Draw();
    quit->Draw();
    ranking->Draw();
    howto->Draw();
    if(play->IsHover()) Texture::GetInstance()->DrawText("PlayTx", "Play Game!", 420, 440, 0.5);
    else Texture::GetInstance()->Drop("PlayTx");
    if(ranking->IsHover()) Texture::GetInstance()->DrawText("RkTx", "See Ranking!", 420, 440, 0.5);
    else Texture::GetInstance()->Drop("RkTx");
    if(quit->IsHover()) Texture::GetInstance()->DrawText("QTx", "Quit Game!", 420, 440, 0.5);
    else Texture::GetInstance()->Drop("QTx");
    if(howto->IsHover()) Texture::GetInstance()->DrawText("HTx", "How to play Game!", 420, 440, 0.5);
    else Texture::GetInstance()->Drop("HTx");
}

void Menu::Clean()
{
    play->Clean();
    quit->Clean();
    ranking->Clean();
    Texture::GetInstance()->Drop("MenuBg");
    Texture::GetInstance()->Drop("Game");
    Sound::GetInstance()->Clean();
}

void Menu::Listen() {
    if(play->IsPressed()) Engine::GetInstance()->ChangeState(Play::GetInstance());
    if(quit->IsPressed()) Engine::GetInstance()->Quit();
}
