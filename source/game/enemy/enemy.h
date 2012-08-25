#pragma once

#include "pixelboost/logic/entity.h"

class Enemy : public pb::Entity
{
public:
    Enemy(pb::Scene* scene);
    ~Enemy();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
};
