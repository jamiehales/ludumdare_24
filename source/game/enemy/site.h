#pragma once

#include "pixelboost/logic/entity.h"

class Site : pb::Entity
{
public:
    Site(pb::Scene* scene, glm::vec3 position, float rotation);
    ~Site();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnUpdate(const pb::Message& message);
};
