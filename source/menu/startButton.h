#pragma once

#include "pixelboost/logic/entity.h"

class MenuStartButton : pb::Entity
{
public:
    MenuStartButton(pb::Scene* scene);
    ~MenuStartButton();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnTouch(const pb::Message& message);
};
