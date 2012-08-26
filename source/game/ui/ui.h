#pragma once

#include "glm/glm.hpp";

#include "pixelboost/logic/entity.h"

namespace pb
{
    class RectangleComponent;
}

class GameUi : pb::Entity
{
public:
    GameUi(pb::Scene* scene, glm::vec3 position);
    ~GameUi();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void SetBarStatus(pb::RectangleComponent* rect, float value, float offset);
    void OnUpdate(const pb::Message& message);
    
    pb::RectangleComponent* _DefenseIndicator;
    pb::RectangleComponent* _SpeedIndicator;
    pb::RectangleComponent* _PowerIndicator;
    pb::RectangleComponent* _FireRateIndicator;
};
