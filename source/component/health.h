#pragma once

#include "pixelboost/logic/component.h"

namespace pb
{
    class EllipseComponent;
    class Message;
}

class HealthComponent : public pb::Component
{
public:
    enum HealthType
    {
        kHealthTypePlayer,
        kHealthTypeEnemy,
    };
    
    HealthComponent(pb::Entity* entity, HealthType type, float health, float armour);
    ~HealthComponent();
    
    virtual pb::Uid GetType();
    static pb::Uid GetStaticType();
    
private:
    void OnCollision(const pb::Message& message);
    
    pb::EllipseComponent* _Visual;
    HealthType _Type;
    float _Health;
    float _Armour;
};
