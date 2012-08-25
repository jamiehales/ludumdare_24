#include "pixelboost/logic/component/graphics/ellipse.h"
#include "pixelboost/logic/component/input/rectTouch.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/input/touch.h"
#include "pixelboost/logic/message/update.h"
#include "pixelboost/logic/system/debug/render.h"
#include "pixelboost/logic/scene.h"

#include "component/target.h"
#include "game/enemy/site.h"
#include "game/player/queen.h"
#include "game/player/ship.h"
#include "game/projectiles/bullet.h"
#include "message/target.h"

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

void Ship::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    
    glm::vec3 position = transform->GetPosition();
    float rotation = glm::radians(transform->GetRotation().z + 90.f);
    
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
    
    glm::vec3 target;
    float maxDistance = 10000.f;
    for (pb::Scene::EntityMap::iterator it = queens.begin(); it != queens.end(); ++it)
    {
        pb::TransformComponent* queenTransform = it->second->GetComponentByType<pb::TransformComponent>();
        float distance = glm::distance(queenTransform->GetPosition(), transform->GetPosition());
        if (distance < maxDistance)
        {
            target = queenTransform->GetPosition();
            maxDistance = distance;
        }
    }
    
    GetScene()->SendMessage(GetUid(), TargetMessage(this, 0, target));
    
    pb::EllipseComponent* ellipse = GetComponentByType<pb::EllipseComponent>();
    ellipse->SetColor(glm::vec4(1,1,1,1));
}
