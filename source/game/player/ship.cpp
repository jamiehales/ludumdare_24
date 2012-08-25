#include "pixelboost/logic/component/graphics/ellipse.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/update.h"

#include "game/player/ship.h"

Ship::Ship(pb::Scene* scene, glm::vec3 position, float rotation)
    : pb::Entity(scene, 0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(position, glm::vec3(0,0,rotation), glm::vec3(1,1,1));
    
    pb::EllipseComponent* ellipse = new pb::EllipseComponent(this);
    ellipse->SetSize(glm::vec2(0.15,0.25));
    ellipse->SetSolid(true);
    ellipse->SetColor(glm::vec4(0,0.8,0,1));
    
    RegisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Ship::OnUpdate));
}

Ship::~Ship()
{
    UnregisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Ship::OnUpdate));
}

pb::Uid Ship::GetType() const
{
    return Ship::GetStaticType();
}

pb::Uid Ship::GetStaticType()
{
    return pb::TypeHash("Ship");
}

void Ship::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    
    glm::vec3 position = transform->GetPosition();
    float rotation = glm::radians(transform->GetRotation().z + 90.f);
    float speed = 1.f * updateMessage.GetDelta();
    
    position = position + glm::vec3(cos(rotation) * speed, sin(rotation) * speed, 0);
    
    transform->SetPosition(position);
    
}
