#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/update.h"

#include "game/enemy/enemy.h"

Enemy::Enemy(pb::Scene* scene, glm::vec3 position, float rotation)
    : pb::Entity(scene, 0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(position, glm::vec3(0,0,rotation), glm::vec3(1,1,1));
    
    pb::RectangleComponent* ellipse = new pb::RectangleComponent(this);
    ellipse->SetSize(glm::vec2(0.15,0.25));
    ellipse->SetSolid(true);
    ellipse->SetColor(glm::vec4(0.8,0,0,1));

    RegisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Enemy::OnUpdate));
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

void Enemy::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    
    glm::vec3 position = transform->GetPosition();
    float rotation = glm::radians(transform->GetRotation().z + 90.f);
    float speed = 0.2f * updateMessage.GetDelta();
    
    position = position + glm::vec3(cos(rotation) * speed, sin(rotation) * speed, 0);
    
    //rotation += GetTargetAngle() * (0.25f * updateMessage.GetDelta());
    
    //GetScene()->GetSystemByType<pb::DebugRenderSystem>()->AddLine(pb::kRenderPassScene, 10, position, _Target, glm::vec4(1,1,1,0.5));
    
    transform->SetPosition(position);
    transform->SetRotation(glm::vec3(0,0,glm::degrees(rotation) - 90.f));
}
