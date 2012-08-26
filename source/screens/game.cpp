#include "pixelboost/graphics/camera/camera.h"
#include "pixelboost/graphics/camera/viewport.h"

#include "game/world.h"
#include "screens/game.h"

GameScreen::GameScreen()
{
    _Camera = new pb::OrthographicCamera();
    _World = new World();

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
