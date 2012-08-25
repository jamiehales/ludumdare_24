#pragma once

#include "pixelboost/logic/entity.h"

class Enemy : public pb::Entity
{
public:
    Enemy(pb::Scene* scene, glm::vec3 position, float rotation);
    ~Enemy();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    float GetTargetAngle();
    void OnUpdate(const pb::Message& message);
    
    glm::vec3 _Target;
    float _FireTime;
    float _FireRate;
};
