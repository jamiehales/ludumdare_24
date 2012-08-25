#include "pixelboost/debug/debugVariable.h"
#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/update.h"

#include "game/enemy/site/spawner.h"
#include "game/enemy/site.h"

DEFINE_DEBUG_FLOAT(g_InitialSiteSpawn, "Site Spawn Initial", 15.f, 0.f, 60.f);
DEFINE_DEBUG_FLOAT(g_SiteSpawnFrequency, "Site Spawn Frequency", 120.f, 0.f, 60.f);

Site::Site(pb::Scene* scene, glm::vec3 position, float rotation)
    : pb::Entity(scene, 0)
    , _Spawned(false)
    , _SpawnTime(g_InitialSiteSpawn)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(position, glm::vec3(0,0,rotation), glm::vec3(1,1,1));
    
    pb::RectangleComponent* rect = new pb::RectangleComponent(this);
    rect->SetSize(glm::vec2(0.5,0.2));
    rect->SetSolid(true);
    rect->SetColor(glm::vec4(0.8,0,0,1));
    
    RegisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Site::OnUpdate));
}

Site::~Site()
{
    
}

pb::Uid Site::GetType() const
{
    return Site::GetStaticType();
}

pb::Uid Site::GetStaticType()
{
    return pb::TypeHash("Site");
}

void Site::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    
    if (!_Spawned)
    {
        _SpawnTime -= updateMessage.GetDelta();
        
        pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
        
        if (_SpawnTime <= 0.f)
        {
            _Spawned = true;
            _SpawnTime = g_SiteSpawnFrequency;
            
            new SpawnerSite(GetScene(), GetUid());
        }
    }
}
