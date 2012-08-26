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
    FireRate = 1.f;
}

void AiDefinition::Adapt(const AiDefinition& definition)
{
    Defense += (definition.Defense - Defense) / 1.5f;
    Power += (definition.Power - Power) / 1.5f;
    Speed += (definition.Speed - Speed) / 1.5f;
    FireRate += (definition.FireRate - FireRate) / 1.5f;
    
    Clamp();
}

void AiDefinition::Devolve(float time)
{
    float devolutionAmount = 0.005f * time;
    
    Defense += (1.f - Defense) * devolutionAmount;
    Power += (1.f - Power) * devolutionAmount;
    Speed += (1.f - Speed) * devolutionAmount;
    FireRate += (1.f - FireRate) * devolutionAmount;
    
    Clamp();
}

AiDefinition AiDefinition::Evolve()
{
    AiDefinition definition = *this;
    
    float evolutionNegativeAmount = 0.35f;
    float evolutionPositiveAmount = 0.35f;
    
    definition.Defense += glm::compRand1(-evolutionNegativeAmount, evolutionPositiveAmount);
    definition.Power += glm::compRand1(-evolutionNegativeAmount, evolutionPositiveAmount);
    definition.Speed += glm::compRand1(-evolutionNegativeAmount, evolutionPositiveAmount);
    definition.FireRate += glm::compRand1(-evolutionNegativeAmount, evolutionPositiveAmount);
    
    definition.Clamp();
    
    return definition;
}

void AiDefinition::Clamp()
{
    Defense = glm::clamp(Defense, 0.f, 2.f);
    Power = glm::clamp(Power, 0.f, 2.f);
    Speed = glm::clamp(Speed, 0.f, 2.f);
    FireRate = glm::clamp(FireRate, 0.f, 2.f);
}

AiComponent::AiComponent(pb::Entity* entity, AiType type, AiDefinition definition)
    : pb::Component(entity)
    , _Definition(definition)
    , _Type(type)
{
    _FireRate = (_Type == kAiTypePlayer ? 2.f : 4.f) / definition.FireRate;
    _FireTime = _FireRate;
    _Warmup = 15.f;
    
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
    glm::vec3 position = transform->GetPosition();
    
    _Warmup = glm::max(0.f, _Warmup - updateMessage.GetDelta());
    
    _FireTime -= updateMessage.GetDelta();
    if (_FireTime <= 0.f)
    {
        _FireTime += _FireRate;
        
        float basePower = _Type == kAiTypePlayer ? 4.f : 2.f;
        
        new Bullet(GetScene(), _Type == kAiTypePlayer ? Bullet::kBulletSourcePlayer : Bullet::kBulletSourceEnemy, basePower * _Definition.Power, position, transform->GetRotation().z);
        
        glm::vec3 target;
        
        if (_Type == kAiTypePlayer)
        {
            glm::vec3 targetA, targetB;
            bool targetAValid, targetBValid;
            
            targetAValid = static_cast<World*>(GetScene())->FindClosestTarget<SpawnerSite>(position, targetA);
            targetBValid = static_cast<World*>(GetScene())->FindClosestTarget<Enemy>(position, targetB);
            
            if (glm::distance(position, targetB) < glm::distance(position, targetA) && targetBValid)
            {
                target = targetB;
            } else {
                target = targetA;
            }
        } else {
            glm::vec3 targetA, targetB;
            bool targetAValid, targetBValid;
            
            targetAValid = static_cast<World*>(GetScene())->FindClosestTarget<Queen>(position, targetA);
            targetBValid = static_cast<World*>(GetScene())->FindClosestTarget<Ship>(position, targetB);
            
            if (glm::distance(position, targetB) < glm::distance(position, targetA) && targetBValid)
            {
                target = targetB;
            } else {
                target = targetA;
            }
        }

        if (_Warmup <= 0.f || glm::distance(target, position) < 5.f)
        {
            GetScene()->SendMessage(GetParentUid(), TargetMessage(GetParent(), this, target));
        }
    }
}
