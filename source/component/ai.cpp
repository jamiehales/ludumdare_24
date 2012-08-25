#include "pixelboost/logic/message/update.h"

#include "component/ai.h"

AiDefinition::AiDefinition()
{
    Defense = 0.5;
    Power = 0.5;
    Speed = 0.5;
    Avoidance = 0.5;
}

void AiDefinition::Adapt(AiDefinition& definition)
{
    
}

AiComponent::AiComponent(pb::Entity* entity, AiType type, AiDefinition definition)
    : pb::Component(entity)
    , _Definition(definition)
    , _Type(type)
{
    
}

AiComponent::~AiComponent()
{
    
}

void AiComponent::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    
}
