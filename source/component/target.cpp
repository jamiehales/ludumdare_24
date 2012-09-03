#include <math.h>

#include "pixelboost/logic/component/transform.h"
#include "pixelboost/logic/message/update.h"
#include "pixelboost/logic/entity.h"

#include "component/target.h"
#include "message/target.h"

TargetingComponent::TargetingComponent(pb::Entity* entity, float speed)
    : pb::Component(entity)
    , _Speed(speed)
{
    GetParent()->RegisterMessageHandler<pb::UpdateMessage>(pb::Entity::MessageHandler(this, &TargetingComponent::OnUpdate));
    GetParent()->RegisterMessageHandler<TargetMessage>(pb::Entity::MessageHandler(this, &TargetingComponent::OnTarget));
}

TargetingComponent::~TargetingComponent()
{
    GetParent()->UnregisterMessageHandler<pb::UpdateMessage>(pb::Entity::MessageHandler(this, &TargetingComponent::OnUpdate));
    GetParent()->UnregisterMessageHandler<TargetMessage>(pb::Entity::MessageHandler(this, &TargetingComponent::OnTarget));
}

pb::Uid TargetingComponent::GetType()
{
    return TargetingComponent::GetStaticType();
}

pb::Uid TargetingComponent::GetStaticType()
{
    return pb::TypeHash("TargetingComponent");
}

float TargetingComponent::GetTargetAngle()
{
    pb::TransformComponent* transform = GetParent()->GetComponentByType<pb::TransformComponent>();
    glm::vec3 position = transform->GetPosition();
    
    float rotation = glm::radians(transform->GetRotation().z + 90.f);
    float targetRotation = glm::atan(_Target.y-position.y, _Target.x-position.x);
    
    float angle = glm::mod(glm::abs(rotation-targetRotation), (float)M_PI*2.f) + M_PI;
    
    if (angle >= M_PI)
        angle = -M_PI + angle;
    
    return angle - glm::radians(90.f);
}

void TargetingComponent::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    pb::TransformComponent* transform = GetParent()->GetComponentByType<pb::TransformComponent>();
    
    glm::vec3 position = transform->GetPosition();
    float rotation = glm::radians(transform->GetRotation().z + 90.f);
    float speed = _Speed * updateMessage.GetDelta();
    
    position = position + glm::vec3(cos(rotation) * speed, sin(rotation) * speed, 0);
    
    rotation += GetTargetAngle() * (0.25f * updateMessage.GetDelta());
    
    transform->SetPosition(position);
    transform->SetRotation(glm::vec3(0,0,glm::degrees(rotation) - 90.f));
}

void TargetingComponent::OnTarget(const pb::Message& message)
{
    const TargetMessage& targetMessage = static_cast<const TargetMessage&>(message);
    _Target = targetMessage.GetTarget();
}
