#pragma once

#include "glm/glm.hpp"

#include "pixelboost/logic/message.h"

class TargetMessage : public pb::Message
{
public:
    TargetMessage(pb::Entity* entity, pb::Component* component, glm::vec3 target);
    ~TargetMessage();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
    const glm::vec3& GetTarget() const;
    
private:
    glm::vec3 _Target;
};
