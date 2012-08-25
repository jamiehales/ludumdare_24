#pragma once

#include "glm/glm.hpp"

#include "pixelboost/logic/scene.h"

class World : public pb::Scene
{
public:
    World();
    ~World();
    
    template <class T> bool FindClosestTarget(glm::vec3 position, glm::vec3& target);
};

#include "game/world.inl"
