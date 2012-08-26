#pragma once

#include "pixelboost/logic/entity.h"

class AiDefinition;

class Enemy : public pb::Entity
{
public:
    Enemy(pb::Scene* scene, const AiDefinition& definition, glm::vec3 position, float rotation);
    ~Enemy();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
};
