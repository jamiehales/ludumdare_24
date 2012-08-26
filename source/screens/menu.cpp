#include "pixelboost/graphics/camera/camera.h"
#include "pixelboost/graphics/camera/viewport.h"
#include "pixelboost/logic/system/debug/render.h"
#include "pixelboost/logic/system/graphics/render/bounds.h"
#include "pixelboost/logic/scene.h"

#include "game/background.h"
#include "menu/start.h"
#include "menu/title.h"
#include "screens/menu.h"

MenuScreen::MenuScreen()
{
    _Camera = new pb::OrthographicCamera();
    _Scene = new pb::Scene();
    _Scene->AddSystem(new pb::BoundsRenderSystem());
    _Scene->AddSystem(new pb::DebugRenderSystem());
    
    pb::Viewport* viewport = new pb::Viewport(0, _Camera);
    viewport->SetScene(_Scene);
    AddViewport(viewport);
    
    new Background(_Scene);
    new MenuTitle(_Scene);
    new MenuStart(_Scene);
}

MenuScreen::~MenuScreen()
{
    
}

void MenuScreen::Update(float time)
{
    _Scene->Update(time);
    
    pb::Screen::Update(time);
}
