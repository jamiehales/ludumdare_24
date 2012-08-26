#pragma once

#include "pixelboost/logic/entity.h"

class Explosion : public pb::Entity
{
public:
    Explosion(pb::Scene* scene, glm::vec3 position);
    ~Explosion();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnUpdate(const pb::Message& message);
    
    float _Time;
};
