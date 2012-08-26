#pragma once

#include "pixelboost/logic/entity.h"

namespace pb
{
    class LineComponent;
}

class GameUi : pb::Entity
{
public:
    GameUi(pb::Scene* scene, glm::vec3 position);
    ~GameUi();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnUpdate(const pb::Message& message);
    
    pb::LineComponent* _DefenseIndicator;
    pb::LineComponent* _SpeedIndicator;
    pb::LineComponent* _PowerIndicator;
    pb::LineComponent* _AvoidanceIndicator;
};
