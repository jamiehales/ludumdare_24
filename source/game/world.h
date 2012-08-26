#pragma once

#include "glm/glm.hpp"

#include "pixelboost/logic/scene.h"

class AiDefinition;

struct Difficulty
{
    int EnemyShortWaveCount;
    float EnemyShortWaveLengthMultiplier;
};

class World : public pb::Scene
{
public:
    enum DifficultyOption
    {
        kDifficultyEasy,
        kDifficultyNormal,
        kDifficultyHard,
    };
    
    World(DifficultyOption difficulty);
    ~World();
    
    Difficulty GetDifficulty();
    
    AiDefinition& GetEnemyAiDefinition();
    AiDefinition& GetPlayerAiDefinition();
    
    template <class T> bool FindClosestTarget(glm::vec3 position, glm::vec3& target);
    
private:
    Difficulty _Difficulty;
    
    AiDefinition* _EnemyAi;
    AiDefinition* _PlayerAi;
};

#include "game/world.inl"
