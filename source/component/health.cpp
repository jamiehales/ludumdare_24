#include "pixelboost/logic/component/physics/physics.h"
#include "pixelboost/logic/message/physics/collision.h"

#include "component/health.h"
#include "game/projectiles/bullet.h"

HealthComponent::HealthComponent(pb::Entity* entity, HealthType type, float health, float armour)
    : pb::Component(entity)
    , _Health(health)
    , _Type(type)
    , _Armour(armour)
{
    GetParent()->RegisterMessageHandler<pb::PhysicsCollisionMessage>(pb::Entity::MessageHandler(this, &HealthComponent::OnCollision));
}

HealthComponent::~HealthComponent()
{
    GetParent()->UnregisterMessageHandler<pb::PhysicsCollisionMessage>(pb::Entity::MessageHandler(this, &HealthComponent::OnCollision));
}

pb::Uid HealthComponent::GetType()
{
    return HealthComponent::GetStaticType();
}

pb::Uid HealthComponent::GetStaticType()
{
    return pb::TypeHash("HealthComponent");
}

void HealthComponent::OnCollision(const pb::Message& message)
{
    const pb::PhysicsCollisionMessage& collisionMessage = static_cast<const pb::PhysicsCollisionMessage&>(message);
    
    if (collisionMessage.GetOtherComponent()->GetParent()->GetType() == Bullet::GetStaticType())
    {
        Bullet* bullet = static_cast<Bullet*>(collisionMessage.GetOtherComponent()->GetParent());
        
        bool takeDamage = false;
        
        if (_Type == kHealthTypeEnemy && bullet->GetSource() == Bullet::kBulletSourcePlayer)
        {
            takeDamage = true;
        }
        
        if (_Type == kHealthTypePlayer && bullet->GetSource() == Bullet::kBulletSourceEnemy)
        {
            takeDamage = true;
        }
        
        if (takeDamage)
        {
            _Health -= bullet->GetPower() / _Armour;
            
            if (_Health <= 0.f)
            {
                GetParent()->Destroy();
            }
            
            bullet->Destroy();
        }
    }
}
