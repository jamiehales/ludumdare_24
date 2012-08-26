#pragma once

#include "pixelboost/logic/entity.h"

class SpawnerSite : public pb::Entity
{
public:
    SpawnerSite(pb::Scene* scene, pb::Uid site);
    ~SpawnerSite();
    
    virtual pb::Uid GetType() const;
    static pb::Uid GetStaticType();
    
    void OnUpdate(const pb::Message& message);
    
private:
    bool _ShortWave;
    float _SpawnTime;
    pb::Uid _SiteUid;
};
