#pragma once

#include "pixelboost/logic/entity.h"

class Enemy : public pb::Entity
{
public:
    Enemy(pb::Scene* scene, glm::vec3 position, float rotation);
    ~Enemy();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
    void OnUpdate(const pb::Message& message);
};
