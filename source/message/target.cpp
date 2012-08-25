#include "message/target.h"

TargetMessage::TargetMessage(pb::Entity* entity, pb::Component* component, glm::vec3 target)
    : pb::Message(entity, component)
    , _Target(target)
{
    
}

TargetMessage::~TargetMessage()
{
    
}

pb::Uid TargetMessage::GetType() const
{
    return TargetMessage::GetStaticType();
}

pb::Uid TargetMessage::GetStaticType()
{
    return pb::TypeHash("TargetMessage");
}

const glm::vec3& TargetMessage::GetTarget() const
{
    return _Target;
}
