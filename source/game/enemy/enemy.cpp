#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/update.h"
#include "pixelboost/logic/scene.h"

#include "game/enemy/enemy.h"
#include "game/player/queen.h"
#include "game/projectiles/bullet.h"

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
    
    float maxDistance = 10000.f;
    for (pb::Scene::EntityMap::iterator it = sites.begin(); it != sites.end(); ++it)
    {
        pb::TransformComponent* siteTransform = it->second->GetComponentByType<pb::TransformComponent>();
        float distance = glm::distance(siteTransform->GetPosition(), transform->GetPosition());
        if (distance < maxDistance)
        {
            _Target = siteTransform->GetPosition();
            maxDistance = distance;
        }
    }

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

float Enemy::GetTargetAngle()
{
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    glm::vec3 position = transform->GetPosition();
    
    float rotation = glm::radians(transform->GetRotation().z + 90.f);
    float targetRotation = glm::atan(_Target.y-position.y, _Target.x-position.x);
    
    float angle = glm::mod(glm::abs(rotation-targetRotation), (float)M_PI*2.f) + M_PI;
    
    if (angle >= M_PI)
        angle = -M_PI + angle;
    
    return angle - glm::radians(90.f);
}

void Enemy::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    
    glm::vec3 position = transform->GetPosition();
    float rotation = glm::radians(transform->GetRotation().z + 90.f);
    float speed = 0.2f * updateMessage.GetDelta();
    
    position = position + glm::vec3(cos(rotation) * speed, sin(rotation) * speed, 0);
    
    rotation += GetTargetAngle() * (0.25f * updateMessage.GetDelta());
    
    //GetScene()->GetSystemByType<pb::DebugRenderSystem>()->AddLine(pb::kRenderPassScene, 10, position, _Target, glm::vec4(1,1,1,0.5));
    
    transform->SetPosition(position);
    transform->SetRotation(glm::vec3(0,0,glm::degrees(rotation) - 90.f));
    
    _FireTime -= updateMessage.GetDelta();
    if (_FireTime <= 0.f)
    {
        _FireTime += _FireRate;
        new Bullet(GetScene(), position, glm::degrees(rotation) - 90.f);
    }
}
