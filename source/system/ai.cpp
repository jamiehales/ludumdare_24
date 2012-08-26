#include "pixelboost/logic/scene.h"

#include "component/ai.h"
#include "game/enemy/site/spawner.h"
#include "game/enemy/enemy.h"
#include "game/player/queen.h"
#include "game/player/ship.h"
#include "game/game.h"
#include "game/world.h"
#include "system/ai.h"

AiSystem::AiSystem()
    : _New(true)
{
    
}

AiSystem::~AiSystem()
{
    
}

pb::Uid AiSystem::GetType() const
{
    return GetStaticType();
}

pb::Uid AiSystem::GetStaticType()
{
    return pb::TypeHash("AiSystem");
}

void AiSystem::Update(pb::Scene* scene, float time)
{
    static_cast<World*>(scene)->GetPlayerAiDefinition().Devolve(time);
    
    if (_New)
    {
        _New = false;
        return;
    }
    
    pb::Scene::EntityMap spawners = scene->GetEntitiesByType<SpawnerSite>();
    pb::Scene::EntityMap queens = scene->GetEntitiesByType<Queen>();
    
    if (spawners.size() == 0)
    {
        pb::Scene::EntityMap enemies = scene->GetEntitiesByType<Enemy>();
        
        if (enemies.size() == 0)
        {
            Game::Instance()->Transition(Game::kGameModeEnd, true);
            return;
        }
    }
    
    if (queens.size() == 0)
    {
        pb::Scene::EntityMap ships = scene->GetEntitiesByType<Ship>();
        
        if (ships.size() == 0)
        {
            Game::Instance()->Transition(Game::kGameModeEnd, false);
            return;
        }
    }
}
