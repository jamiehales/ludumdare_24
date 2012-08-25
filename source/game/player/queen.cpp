#include "pixelboost/debug/debugVariable.h"
#include "pixelboost/logic/component/graphics/ellipse.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/update.h"

#include "game/player/queen.h"
#include "game/player/ship.h"

DEFINE_DEBUG_FLOAT(g_QueenSpawnFrequency, "Queen Spawn Frequency", 30.f, 0.f, 60.f);

Queen::Queen(pb::Scene* scene, glm::vec3 position, float rotation)
    : pb::Entity(scene, 0)
    , _SpawnTime(0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(position, glm::vec3(0,0,rotation), glm::vec3(1,1,1));
    
    pb::EllipseComponent* ellipse = new pb::EllipseComponent(this);
    ellipse->SetSize(glm::vec2(1,0.5));
    ellipse->SetSolid(true);
    
    RegisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Queen::OnUpdate));
}

Queen::~Queen()
{
    UnregisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Queen::OnUpdate));
}

pb::Uid Queen::GetType() const
{
    return Queen::GetStaticType();
}

pb::Uid Queen::GetStaticType()
{
    return pb::TypeHash("Queen");
}

void Queen::OnUpdate(const pb::Message& message)
{
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    _SpawnTime -= updateMessage.GetDelta();
    
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    
    if (_SpawnTime <= 0.f)
    {
        _SpawnTime = g_QueenSpawnFrequency;
        
        new Ship(GetScene(), transform->GetPosition(), transform->GetRotation().z + 180.f);
    }
}
