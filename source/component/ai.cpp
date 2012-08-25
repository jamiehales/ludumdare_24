#include "pixelboost/logic/message/update.h"

#include "component/ai.h"

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
