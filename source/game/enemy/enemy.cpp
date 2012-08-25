#include "game/enemy/enemy.h"

Enemy::Enemy(pb::Scene* scene)
    : pb::Entity(scene, 0)
{
    
}

Enemy::~Enemy()
{
    
}

pb::Uid Enemy::GetType() const
{
    return Enemy::GetStaticType();
}

pb::Uid Enemy::GetStaticType()
{
    return pb::TypeHash("Enemy");
}
