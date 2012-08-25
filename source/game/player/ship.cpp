#include "pixelboost/logic/component/graphics/ellipse.h"
#include "pixelboost/logic/component/input/rectTouch.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/input/touch.h"
#include "pixelboost/logic/message/update.h"
#include "pixelboost/logic/system/debug/render.h"
#include "pixelboost/logic/scene.h"

#include "game/enemy/site.h"
#include "game/player/queen.h"
#include "game/player/ship.h"
#include "game/projectiles/bullet.h"

Ship::Ship(pb::Scene* scene, glm::vec3 position, float rotation)
    : pb::Entity(scene, 0)
{
    _FireRate = 2.f;
    _FireTime = _FireRate;
    _ReturningHome = false;

    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(position, glm::vec3(0,0,rotation), glm::vec3(1,1,1));
    
    pb::EllipseComponent* ellipse = new pb::EllipseComponent(this);
    ellipse->SetSize(glm::vec2(0.15,0.25));
    ellipse->SetSolid(true);
    ellipse->SetColor(glm::vec4(0,0.8,0,1));
    
    pb::RectTouchComponent* touch = new pb::RectTouchComponent(this);
    touch->SetSize(glm::vec2(1.f, 1.f));
    
    pb::Scene::EntityMap sites = GetScene()->GetEntitiesByType<Site>();
    
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
    
    RegisterMessageHandler<pb::TouchDownMessage>(MessageHandler(this, &Ship::OnTouch));
    RegisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Ship::OnUpdate));
}

Ship::~Ship()
{
    UnregisterMessageHandler<pb::TouchDownMessage>(MessageHandler(this, &Ship::OnTouch));
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

float Ship::GetTargetAngle()
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

void Ship::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    
    glm::vec3 position = transform->GetPosition();
    float rotation = glm::radians(transform->GetRotation().z + 90.f);
    float speed = 0.2f * updateMessage.GetDelta();
    
    position = position + glm::vec3(cos(rotation) * speed, sin(rotation) * speed, 0);
    
    rotation += GetTargetAngle() * (0.25f * updateMessage.GetDelta());
    
    transform->SetPosition(position);
    transform->SetRotation(glm::vec3(0,0,glm::degrees(rotation) - 90.f));
    
    if (!_ReturningHome)
    {
        _FireTime -= updateMessage.GetDelta();
        if (_FireTime <= 0.f)
        {
            _FireTime += _FireRate;
            new Bullet(GetScene(), position, glm::degrees(rotation) - 90.f);
        }
    }
}

void Ship::OnTouch(const pb::Message& message)
{
    _ReturningHome = true;
    
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    pb::Scene::EntityMap queens = GetScene()->GetEntitiesByType<Queen>();
    
    float maxDistance = 10000.f;
    for (pb::Scene::EntityMap::iterator it = queens.begin(); it != queens.end(); ++it)
    {
        pb::TransformComponent* queenTransform = it->second->GetComponentByType<pb::TransformComponent>();
        float distance = glm::distance(queenTransform->GetPosition(), transform->GetPosition());
        if (distance < maxDistance)
        {
            _Target = queenTransform->GetPosition();
            maxDistance = distance;
        }
    }
    
    pb::EllipseComponent* ellipse = GetComponentByType<pb::EllipseComponent>();
    ellipse->SetColor(glm::vec4(1,1,1,1));
}
