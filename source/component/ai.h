#pragma once

#include "pixelboost/logic/component.h"

namespace pb
{
    class Message;
}

enum AiType
{
    kAiTypePlayer,
    kAiTypeEnemy
};

class AiDefinition
{
public:
    AiDefinition();
    void Adapt(AiDefinition& definition);
    
public:
    float Defense;
    float Speed;
    float Power;
    float Avoidance;
};

class AiComponent : public pb::Component
{
public:
    AiComponent(pb::Entity* entity, AiType type, const AiDefinition definition);
    ~AiComponent();
    
private:
    void OnUpdate(const pb::Message& message);
    
    AiDefinition _Definition;
    AiType _Type;
};
