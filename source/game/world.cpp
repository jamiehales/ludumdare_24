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
    AddSystem(new pb::BoundsRenderSystem());
    AddSystem(new pb::DebugRenderSystem());
    
    pb::PhysicsSystem2D* physicsSystem = new pb::PhysicsSystem2D();
    //physicsSystem->SetDebugRender(true);
    AddSystem(physicsSystem);
    
    new Background(this);
    
    new GameUi(this, glm::vec3(0, 10.5f, 0));
    new GameUi(this, glm::vec3(0, -10.5f, 0));
    
    new Planet(this);
    
    new Queen(this, glm::vec3(14, 10, 0), -45.f);
    new Queen(this, glm::vec3(-14, 10, 0), 45.f);
    new Queen(this, glm::vec3(14, -10, 0), 225.f);
    new Queen(this, glm::vec3(-14, -10, 0), 135.f);
    
    int numSites = 10;
    for (int i=0; i<numSites; i++)
    {
        float angle = i * (360.f / numSites);
        new Site(this, glm::vec3(cos(glm::radians(angle))*3.f, sin(glm::radians(angle))*3.f, 0), angle + 90.f);
    }
}

World::~World()
{
    
}
