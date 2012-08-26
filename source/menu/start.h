#pragma once

#include "pixelboost/logic/entity.h"

namespace pb
{
    class RectTouchComponent;
}

class MenuStart : pb::Entity
{
public:
    MenuStart(pb::Scene* scene);
    ~MenuStart();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnTouch(const pb::Message& message);
    
    pb::RectTouchComponent* _EasyTouch;
    pb::RectTouchComponent* _MediumTouch;
    pb::RectTouchComponent* _HardTouch;
};
