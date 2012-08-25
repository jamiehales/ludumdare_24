#pragma once

namespace pb
{
    class Scene;
}

class World
{
public:
    World();
    ~World();
    
    pb::Scene* GetScene();
    
    void Update(float time);
    
private:
    pb::Scene* _Scene;
};
