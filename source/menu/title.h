#pragma once

#include "pixelboost/logic/entity.h"

class MenuTitle : pb::Entity
{
public:
    MenuTitle(pb::Scene* scene);
    ~MenuTitle();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
};
