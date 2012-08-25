#pragma once

#include "pixelboost/logic/entity.h"

class GameUi : pb::Entity
{
public:
    GameUi(pb::Scene* scene, glm::vec3 position);
    ~GameUi();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
private:
    void OnUpdate(const pb::Message& message);
};
