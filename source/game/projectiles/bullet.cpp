#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/component/physics/2d/userBody.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/physics/collision.h"
#include "pixelboost/logic/message/update.h"

#include "game/projectiles/bullet.h"

Bullet::Bullet(pb::Scene* scene, BulletSource source, glm::vec3 position, float rotation)
    : pb::Entity(scene, 0)
    , _Source(source)
{
    glm::vec2 bulletSize(0.06, 0.14);
    
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(position - glm::vec3(0,0,1), glm::vec3(0,0,rotation), glm::vec3(1,1,1));
    
    pb::RectangleComponent* rectangle = new pb::RectangleComponent(this);
    rectangle->SetSize(bulletSize);
    rectangle->SetColor(glm::vec4(1,1,1,1));
    rectangle->SetSolid(true);
    
    pb::PhysicsUserBody2DComponent* physicsBody = new pb::PhysicsUserBody2DComponent(this, pb::PhysicsUserBody2DComponent::kBodyTypeDynamic, pb::PhysicsUserBody2DComponent::kBodyShapeRect, bulletSize);
    physicsBody->SetSensor(true);
    
    RegisterMessageHandler<pb::PhysicsCollisionMessage>(MessageHandler(this, &Bullet::OnCollision));
    RegisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Bullet::OnUpdate));
}

Bullet::~Bullet()
{
    UnregisterMessageHandler<pb::PhysicsCollisionMessage>(MessageHandler(this, &Bullet::OnCollision));
    UnregisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Bullet::OnUpdate));
}

pb::Uid Bullet::GetType() const
{
    return Bullet::GetStaticType();
}

pb::Uid Bullet::GetStaticType()
{
    return pb::TypeHash("Bullet");
}

Bullet::BulletSource Bullet::GetSource()
{
    return _Source;
}

void Bullet::OnCollision(const pb::Message& message)
{
    const pb::PhysicsCollisionMessage& collisionMessage = static_cast<const pb::PhysicsCollisionMessage&>(message);
    
    if (collisionMessage.GetOtherComponent()->GetParent()->GetType() == Bullet::GetStaticType())
    {
        Destroy();
    }
//    Destroy();
}

void Bullet::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    
    glm::vec3 position = transform->GetPosition();
    float rotation = glm::radians(transform->GetRotation().z + 90.f);
    float speed = 0.7f * updateMessage.GetDelta();
    
    position = position + glm::vec3(cos(rotation)*speed, sin(rotation)*speed, 0.f);
    
    transform->SetPosition(position);
}
