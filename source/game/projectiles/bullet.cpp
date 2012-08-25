#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/update.h"

#include "game/projectiles/bullet.h"

Bullet::Bullet(pb::Scene* scene, glm::vec3 position, float rotation)
    : pb::Entity(scene, 0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(position - glm::vec3(0,0,1), glm::vec3(0,0,rotation), glm::vec3(1,1,1));
    
    pb::RectangleComponent* rectangle = new pb::RectangleComponent(this);
    rectangle->SetSize(glm::vec2(0.06, 0.14));
    rectangle->SetColor(glm::vec4(1,1,1,1));
    rectangle->SetSolid(true);
    
    RegisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Bullet::OnUpdate));
}

Bullet::~Bullet()
{
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
