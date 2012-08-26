#pragma once

#include "pixelboost/logic/component.h"

namespace pb
{
    class Message;
}

class AiDefinition
{
public:
    AiDefinition();
    
    void Adapt(const AiDefinition& definition);
    void Devolve(float time);
    AiDefinition Evolve();
    void Clamp();
    
public:
    float Defense;
    float Speed;
    float Power;
    float FireRate;
};

class AiComponent : public pb::Component
{
public:
    enum AiType
    {
        kAiTypePlayer,
        kAiTypeEnemy
    };
    
    AiComponent(pb::Entity* entity, AiType type, AiDefinition definition);
    ~AiComponent();
    
    virtual pb::Uid GetType();
    static pb::Uid GetStaticType();
    
    const AiDefinition& GetDefinition();
    
private:
    void OnUpdate(const pb::Message& message);
    
    AiDefinition _Definition;
    AiType _Type;
    
    float _FireRate;
    float _FireTime;
};
