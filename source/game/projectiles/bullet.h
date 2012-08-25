#pragma once

#include "pixelboost/logic/entity.h"

class Bullet : public pb::Entity
{
public:
    enum BulletSource
    {
        kBulletSourceEnemy,
        kBulletSourcePlayer,
    };
    
    Bullet(pb::Scene* scene, BulletSource bulletSource, float power, glm::vec3 position, float rotation);
    ~Bullet();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
    float GetPower();
    BulletSource GetSource();
    
private:
    void OnCollision(const pb::Message& message);
    void OnUpdate(const pb::Message& message);
    
    float _Power;
    BulletSource _Source;
};
