#pragma once

#include "pixelboost/logic/entity.h"

class EndInfo : pb::Entity
{
public:
    EndInfo(pb::Scene* scene, bool success);
    ~EndInfo();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnTouch(const pb::Message& message);
};
