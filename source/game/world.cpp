#include "pixelboost/logic/system/debug/render.h"
#include "pixelboost/logic/system/graphics/render/bounds.h"
#include "pixelboost/logic/system/physics/2d/physics.h"
#include "pixelboost/logic/scene.h"

#include "game/enemy/site.h"
#include "game/player/queen.h"
#include "game/ui/ui.h"
#include "game/background.h"
#include "game/planet.h"
#include "game/world.h"

World::World()
{
    _Scene = new pb::Scene();
    _Scene->AddSystem(new pb::BoundsRenderSystem());
    _Scene->AddSystem(new pb::DebugRenderSystem());
    
    pb::PhysicsSystem2D* physicsSystem = new pb::PhysicsSystem2D();
    //physicsSystem->SetDebugRender(true);
    _Scene->AddSystem(physicsSystem);
    
    new Background(_Scene);
    
    new GameUi(_Scene, glm::vec3(0, 10.5f, 0));
    new GameUi(_Scene, glm::vec3(0, -10.5f, 0));
    
    new Planet(_Scene);
    
    new Queen(_Scene, glm::vec3(14, 10, 0), -45.f);
    new Queen(_Scene, glm::vec3(-14, 10, 0), 45.f);
    new Queen(_Scene, glm::vec3(14, -10, 0), 225.f);
    new Queen(_Scene, glm::vec3(-14, -10, 0), 135.f);
    
    int numSites = 10;
    for (int i=0; i<numSites; i++)
    {
        float angle = i * (360.f / numSites);
        new Site(_Scene, glm::vec3(cos(glm::radians(angle))*3.f, sin(glm::radians(angle))*3.f, 0), angle + 90.f);
    }
}

World::~World()
{
    delete _Scene;
}

pb::Scene* World::GetScene()
{
    return _Scene;
}

void World::Update(float time)
{
    _Scene->Update(time);
}
