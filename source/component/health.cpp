#include "glm/gtc/matrix_transform.hpp"

#include "pixelboost/logic/component/graphics/ellipse.h"
#include "pixelboost/logic/component/physics/physics.h"
#include "pixelboost/logic/component/transform.h"
#include "pixelboost/logic/message/physics/collision.h"

#include "component/health.h"
#include "game/projectiles/bullet.h"
#include "game/explosion.h"

HealthComponent::HealthComponent(pb::Entity* entity, HealthType type, float health, float armour)
    : pb::Component(entity)
    , _Health(health)
    , _Type(type)
    , _Armour(armour)
{
    _Visual = new pb::EllipseComponent(GetParent());
    _Visual->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,0,-1)));
    _Visual->SetSize(glm::vec2(0.5f, 0.5f) * _Health);
    _Visual->SetColor(glm::vec4(0.6,0.6,1,0.5));
    _Visual->SetSolid(true);
    
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
        
        if ((_Type == kHealthTypeEnemy && bullet->GetSource() == Bullet::kBulletSourcePlayer) ||
            (_Type == kHealthTypePlayer && bullet->GetSource() == Bullet::kBulletSourceEnemy))
        {
            _Health -= bullet->GetPower() / _Armour;
            
            _Visual->SetSize(glm::vec2(0.5f, 0.5f) * glm::max(_Health, 0.f));
            
            if (_Health <= 0.f)
            {
                pb::TransformComponent* transform = GetParent()->GetComponentByType<pb::TransformComponent>();
                new Explosion(GetScene(), transform->GetPosition());
                GetParent()->Destroy();
            }
            
            bullet->Destroy();
        }
    }
}
