#pragma once

#include "pixelboost/logic/entity.h"

class Background : public pb::Entity
{
public:
    Background(pb::Scene* scene);
    ~Background();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
};
