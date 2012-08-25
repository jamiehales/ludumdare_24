#pragma once

#include "pixelboost/logic/entity.h"

class Ship : public pb::Entity
{
public:
    Ship(pb::Scene* scene, glm::vec3 position, float rotation);
    ~Ship();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnUpdate(const pb::Message& message);
};
