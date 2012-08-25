#pragma once

#include "pixelboost/logic/entity.h"

class Site : pb::Entity
{
public:
    Site(pb::Scene* scene);
    ~Site();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnUpdate(const pb::Message& message);
};
