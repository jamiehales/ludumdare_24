#pragma once

#include "pixelboost/framework/screen.h"

namespace pb
{
    class OrthographicCamera;
    class Scene;
}

class EndScreen : public pb::Screen
{
public:
    EndScreen();
    ~EndScreen();
    
    virtual void Update(float time);
    
private:
    pb::OrthographicCamera* _Camera;
    pb::Scene* _Scene;
};
