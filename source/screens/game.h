#pragma once

#include "pixelboost/framework/screen.h"

namespace pb
{
    class OrthographicCamera;
}

class World;

class GameScreen : public pb::Screen
{
public:
    GameScreen();
    ~GameScreen();
    
    virtual void Update(float time);
    
private:
    pb::OrthographicCamera* _Camera;
    World* _World;
};
