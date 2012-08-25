#pragma once

#include "pixelboost/logic/component.h"

class TargetingComponent : public pb::Component
{
public:
    TargetingComponent(pb::Entity* entity, float speed);
    ~TargetingComponent();
    
    virtual pb::Uid GetType();
    static pb::Uid GetStaticType();
    
private:
    float GetTargetAngle();

    void OnUpdate(const pb::Message& message);
    void OnTarget(const pb::Message& message);

    float _Speed;
    glm::vec3 _Target;
};
