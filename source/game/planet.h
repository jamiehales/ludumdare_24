#pragma once

#include "pixelboost/logic/entity.h"

class Planet : public pb::Entity
{
public:
    Planet(pb::Scene* scene);
    ~Planet();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
};
