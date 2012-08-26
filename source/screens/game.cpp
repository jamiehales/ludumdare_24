#include "pixelboost/graphics/camera/camera.h"
#include "pixelboost/graphics/camera/viewport.h"

#include "game/world.h"
#include "screens/game.h"

GameScreen::GameScreen(int params)
{
    _Camera = new pb::OrthographicCamera();
    
    switch (params)
    {
        case 0:
            _World = new World(World::kDifficultyEasy);
            break;
        case 1:
            _World = new World(World::kDifficultyMedium);
            break;
        case 2:
            _World = new World(World::kDifficultyHard);
            break;
    }

    pb::Viewport* viewport = new pb::Viewport(0, _Camera);
    viewport->SetScene(_World);
    AddViewport(viewport);
}

GameScreen::~GameScreen()
{

}

void GameScreen::Update(float time)
{
    _World->Update(time);
    
    pb::Screen::Update(time);
}
