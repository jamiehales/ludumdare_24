#pragma once

#include "pixelboost/logic/entity.h"

class Bullet : public pb::Entity
{
public:
    Bullet(pb::Scene* scene, glm::vec3 position, float rotation);
    ~Bullet();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnUpdate(const pb::Message& message);
};
