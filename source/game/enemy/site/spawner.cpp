#include "glm/gtc/matrix_transform.hpp"

#include "pixelboost/debug/debugVariable.h"
#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/component/physics/2d/userBody.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/update.h"
#include "pixelboost/logic/scene.h"

#include "component/ai.h"
#include "component/health.h"
#include "game/enemy/site/spawner.h"
#include "game/enemy/enemy.h"
#include "game/world.h"

DEFINE_DEBUG_FLOAT(g_SpawnerSiteSpawnFrequencyShort, "Spawner Site Spawn FrequencyA", 5.f, 0.f, 60.f);
DEFINE_DEBUG_FLOAT(g_SpawnerSiteSpawnFrequencyLong, "Spawner Site Spawn FrequencyB", 17.5f, 0.f, 60.f);

SpawnerSite::SpawnerSite(pb::Scene* scene, pb::Uid site)
    : pb::Entity(scene, 0)
    , _SiteUid(site)
    , _SpawnTime(0)
    , _ShortWave(1)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    pb::TransformComponent* siteTransform = GetScene()->GetEntityById(site)->GetComponentByType<pb::TransformComponent>();
    transform->SetTransform(siteTransform->GetPosition(), siteTransform->GetRotation() + glm::vec3(0,0,180), siteTransform->GetScale());
    
    pb::RectangleComponent* rect = new pb::RectangleComponent(this);
    rect->SetSize(glm::vec2(0.35,0.6));
    rect->SetSolid(true);
    rect->SetColor(glm::vec4(0.8,0,0,1));
    rect->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,0.3,0)));
    
    pb::PhysicsUserBody2DComponent* physics = new pb::PhysicsUserBody2DComponent(this, pb::PhysicsUserBody2DComponent::kBodyTypeDynamic, pb::PhysicsUserBody2DComponent::kBodyShapeRect, glm::vec2(0.5,0.2)/*sprite->GetSize()*/);
    physics->SetSensor(true);
    
    new HealthComponent(this, HealthComponent::kHealthTypeEnemy, 7.f, 7.f);
    
    RegisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &SpawnerSite::OnUpdate));
}

SpawnerSite::~SpawnerSite()
{
    
}

pb::Uid SpawnerSite::GetType() const
{
    return SpawnerSite::GetStaticType();
}

pb::Uid SpawnerSite::GetStaticType()
{
    return pb::TypeHash("SpawnerSite");
}

void SpawnerSite::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    _SpawnTime -= updateMessage.GetDelta();

    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();

    if (_SpawnTime <= 0.f)
    {
        if (_ShortWave > 0)
        {
            _SpawnTime = g_SpawnerSiteSpawnFrequencyShort * static_cast<World*>(GetScene())->GetDifficulty().EnemyShortWaveLengthMultiplier;
            _ShortWave--;
        }
        else
        {
            _ShortWave = static_cast<World*>(GetScene())->GetDifficulty().EnemyShortWaveCount;
            _SpawnTime = g_SpawnerSiteSpawnFrequencyLong;
        }
        
        float angle = glm::radians(transform->GetRotation().z + 90.f);
        new Enemy(GetScene(), static_cast<World*>(GetScene())->GetEnemyAiDefinition().Evolve(), transform->GetPosition() + glm::vec3(cos(angle)*0.3f, sin(angle)*0.3f, 0.f), transform->GetRotation().z);
    }
}
