#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/component/physics/2d/userBody.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/physics/collision.h"
#include "pixelboost/logic/message/update.h"
#include "pixelboost/logic/scene.h"

#include "component/target.h"
#include "game/enemy/enemy.h"
#include "game/player/queen.h"
#include "game/projectiles/bullet.h"
#include "message/target.h"

Enemy::Enemy(pb::Scene* scene, glm::vec3 position, float rotation)
    : pb::Entity(scene, 0)
{
    _FireRate = 3.f;
    _FireTime = _FireRate;
    
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(position, glm::vec3(0,0,rotation), glm::vec3(1,1,1));
    
    pb::RectangleComponent* ellipse = new pb::RectangleComponent(this);
    ellipse->SetSize(glm::vec2(0.15,0.25));
    ellipse->SetSolid(true);
    ellipse->SetColor(glm::vec4(0.8,0,0,1));
    
    pb::Scene::EntityMap sites = GetScene()->GetEntitiesByType<Queen>();
    
    glm::vec3 target;
    float maxDistance = 10000.f;
    for (pb::Scene::EntityMap::iterator it = sites.begin(); it != sites.end(); ++it)
    {
        pb::TransformComponent* siteTransform = it->second->GetComponentByType<pb::TransformComponent>();
        float distance = glm::distance(siteTransform->GetPosition(), transform->GetPosition());
        if (distance < maxDistance)
        {
            target = siteTransform->GetPosition();
            maxDistance = distance;
        }
    }
    
    new TargetingComponent(this, 0.2f);
    GetScene()->SendMessage(GetUid(), TargetMessage(this, 0, target));
    
    pb::PhysicsUserBody2DComponent* physics = new pb::PhysicsUserBody2DComponent(this, pb::PhysicsUserBody2DComponent::kBodyTypeDynamic, pb::PhysicsUserBody2DComponent::kBodyShapeRect, glm::vec2(0.15, 0.25)/*sprite->GetSize()*/);
    physics->SetSensor(true);

    RegisterMessageHandler<pb::PhysicsCollisionMessage>(MessageHandler(this, &Enemy::OnCollision));
    RegisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Enemy::OnUpdate));
}

Enemy::~Enemy()
{
    UnregisterMessageHandler<pb::PhysicsCollisionMessage>(MessageHandler(this, &Enemy::OnCollision));
    UnregisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Enemy::OnUpdate));
}

pb::Uid Enemy::GetType() const
{
    return Enemy::GetStaticType();
}

pb::Uid Enemy::GetStaticType()
{
    return pb::TypeHash("Enemy");
}

void Enemy::OnCollision(const pb::Message& message)
{
    const pb::PhysicsCollisionMessage& collisionMessage = static_cast<const pb::PhysicsCollisionMessage&>(message);
    
    if (collisionMessage.GetOtherComponent()->GetParent()->GetType() == Bullet::GetStaticType())
    {
        Bullet* bullet = static_cast<Bullet*>(collisionMessage.GetOtherComponent()->GetParent());
        if (bullet->GetSource() == Bullet::kBulletSourcePlayer)
        {
            Destroy();
            bullet->Destroy();
        }
    }
}

void Enemy::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    
    glm::vec3 position = transform->GetPosition();
    float rotation = glm::radians(transform->GetRotation().z + 90.f);

    _FireTime -= updateMessage.GetDelta();
    if (_FireTime <= 0.f)
    {
        _FireTime += _FireRate;
        new Bullet(GetScene(), Bullet::kBulletSourceEnemy, position, glm::degrees(rotation) - 90.f);
    }
}
