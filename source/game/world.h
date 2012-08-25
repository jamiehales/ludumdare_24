#pragma once

#include "glm/glm.hpp"

#include "pixelboost/logic/scene.h"

class AiDefinition;

class World : public pb::Scene
{
public:
    World();
    ~World();
    
    AiDefinition& GetEnemyAiDefinition();
    AiDefinition& GetPlayerAiDefinition();
    
    template <class T> bool FindClosestTarget(glm::vec3 position, glm::vec3& target);
    
private:
    AiDefinition* _EnemyAi;
    AiDefinition* _PlayerAi;
};

#include "game/world.inl"
