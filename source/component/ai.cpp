#include "glm/gtx/random.hpp"

#include "pixelboost/logic/message/update.h"

#include "component/ai.h"
#include "game/enemy/site/spawner.h"
#include "game/enemy/enemy.h"
#include "game/player/queen.h"
#include "game/player/ship.h"
#include "game/projectiles/bullet.h"
#include "game/world.h"
#include "message/target.h"

AiDefinition::AiDefinition()
{
    Defense = 1.f;
    Power = 1.f;
    Speed = 1.f;
    Avoidance = 1.f;
}

void AiDefinition::Adapt(const AiDefinition& definition)
{
    Defense += (definition.Defense - Defense) / 2.f;
    Power += (definition.Power - Power) / 2.f;
    Speed += (definition.Speed - Speed) / 2.f;
    Avoidance += (definition.Avoidance - Avoidance) / 2.f;
    
    Clamp();
}

AiDefinition AiDefinition::Evolve()
{
    AiDefinition definition = *this;
    
    float evolutionPositiveAmount = 0.5f;
    float evolutionNegativeAmount = 0.25f;
    
    definition.Defense += glm::compRand1(-evolutionNegativeAmount, evolutionPositiveAmount);
    definition.Power += glm::compRand1(-evolutionNegativeAmount, evolutionPositiveAmount);
    definition.Speed += glm::compRand1(-evolutionNegativeAmount, evolutionPositiveAmount);
    definition.Avoidance += glm::compRand1(-evolutionNegativeAmount, evolutionPositiveAmount);
    
    definition.Clamp();
    
    return definition;
}

void AiDefinition::Clamp()
{
    Defense = glm::clamp(Defense, 0.f, 2.f);
    Power = glm::clamp(Power, 0.f, 2.f);
    Speed = glm::clamp(Speed, 0.f, 2.f);
    Avoidance = glm::clamp(Avoidance, 0.f, 2.f);
}

AiComponent::AiComponent(pb::Entity* entity, AiType type, AiDefinition definition)
    : pb::Component(entity)
    , _Definition(definition)
    , _Type(type)
{
    _FireRate = _Type == kAiTypePlayer ? 2.f : 4.f;
    _FireTime = _FireRate;
    
    GetParent()->RegisterMessageHandler<pb::UpdateMessage>(pb::Entity::MessageHandler(this, &AiComponent::OnUpdate));
}

AiComponent::~AiComponent()
{
    GetParent()->UnregisterMessageHandler<pb::UpdateMessage>(pb::Entity::MessageHandler(this, &AiComponent::OnUpdate));
}

pb::Uid AiComponent::GetType()
{
    return AiComponent::GetStaticType();
}

pb::Uid AiComponent::GetStaticType()
{
    return pb::TypeHash("AiComponent");
}

const AiDefinition& AiComponent::GetDefinition()
{
    return _Definition;
}

void AiComponent::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    pb::TransformComponent* transform = GetParent()->GetComponentByType<pb::TransformComponent>();
    
    _FireTime -= updateMessage.GetDelta();
    if (_FireTime <= 0.f)
    {
        _FireTime += _FireRate;
        
        float basePower = _Type == kAiTypePlayer ? 4.f : 2.f;
        
        new Bullet(GetScene(), _Type == kAiTypePlayer ? Bullet::kBulletSourcePlayer : Bullet::kBulletSourceEnemy, basePower * _Definition.Power, transform->GetPosition(), transform->GetRotation().z);
        
        glm::vec3 target;
        
        if (_Type == kAiTypePlayer)
        {
            if (!static_cast<World*>(GetScene())->FindClosestTarget<SpawnerSite>(transform->GetPosition(), target))
                static_cast<World*>(GetScene())->FindClosestTarget<Enemy>(transform->GetPosition(), target);
        } else {
            if (!static_cast<World*>(GetScene())->FindClosestTarget<Queen>(transform->GetPosition(), target))
                static_cast<World*>(GetScene())->FindClosestTarget<Ship>(transform->GetPosition(), target);
        }
        
        GetScene()->SendMessage(GetUid(), TargetMessage(GetParent(), this, target));
    }
}
