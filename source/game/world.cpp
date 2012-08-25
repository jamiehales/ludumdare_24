#include "pixelboost/logic/system/debug/render.h"
#include "pixelboost/logic/system/graphics/render/bounds.h"
#include "pixelboost/logic/scene.h"

#include "game/enemy/site.h"
#include "game/player/queen.h"
#include "game/planet.h"
#include "game/world.h"

World::World()
{
    _Scene = new pb::Scene();
    _Scene->AddSystem(new pb::BoundsRenderSystem());
    _Scene->AddSystem(new pb::DebugRenderSystem());
    
    new Planet(_Scene);
    
    new Queen(_Scene, glm::vec3(0, 10, 0), 0.f);
    new Queen(_Scene, glm::vec3(0, -10, 0), 180.f);
    new Queen(_Scene, glm::vec3(10, 0, 0), -90.f);
    new Queen(_Scene, glm::vec3(-10, 0, 0), 90.f);
    
    int numSites = 7;
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
