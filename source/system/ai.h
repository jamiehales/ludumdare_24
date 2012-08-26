#pragma once

#include "pixelboost/logic/system.h"

class AiSystem : public pb::SceneSystem
{
public:
    AiSystem();
    ~AiSystem();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
    virtual void Update(pb::Scene* scene, float time);
    
private:
    bool _New;
};
