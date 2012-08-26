#pragma once

#include "pixelboost/framework/screen.h"

namespace pb
{
    class OrthographicCamera;
    class Scene;
}

class World;

class MenuScreen : public pb::Screen
{
public:
    MenuScreen();
    ~MenuScreen();
    
    virtual void Update(float time);
    
private:
    pb::OrthographicCamera* _Camera;
    pb::Scene* _Scene;
};
