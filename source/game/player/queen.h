#pragma once

#include "pixelboost/logic/entity.h"

class Queen : public pb::Entity
{
public:
    Queen(pb::Scene* scene, glm::vec3 position, float rotation);
    ~Queen();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnCollision(const pb::Message& message);
    void OnUpdate(const pb::Message& message);
    
    float _SpawnTime;
    bool _ShortWave;
};
