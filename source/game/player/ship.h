#pragma once

#include "pixelboost/logic/entity.h"

class AiDefinition;

class Ship : public pb::Entity
{
public:
    Ship(pb::Scene* scene, const AiDefinition& definition, glm::vec3 position, float rotation);
    ~Ship();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnTouch(const pb::Message& message);
};
