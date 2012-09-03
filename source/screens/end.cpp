#include "pixelboost/graphics/camera/camera.h"
#include "pixelboost/graphics/camera/viewport.h"
#include "pixelboost/logic/system/debug/render.h"
#include "pixelboost/logic/system/graphics/render/bounds.h"
#include "pixelboost/logic/scene.h"

#include "game/background.h"
#include "menu/end.h"
#include "screens/end.h"

EndScreen::EndScreen(int params)
{
    _Camera = new pb::OrthographicCamera();
    _Scene = new pb::Scene();
    _Scene->AddSystem(new pb::BoundsRenderSystem());
    _Scene->AddSystem(new pb::DebugRenderSystem());
    
    new Background(_Scene);
    new EndInfo(_Scene, static_cast<bool>(params));
    
    pb::Viewport* viewport = new pb::Viewport(0, _Camera);
    viewport->SetScene(_Scene);
    AddViewport(viewport);
}

EndScreen::~EndScreen()
{
    
}

void EndScreen::Update(float time)
{
    _Scene->Update(time);
    
    pb::Screen::Update(time);
}