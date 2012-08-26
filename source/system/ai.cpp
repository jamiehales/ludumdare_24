#include "component/ai.h"
#include "game/world.h"
#include "system/ai.h"

AiSystem::AiSystem()
{
    
}

AiSystem::~AiSystem()
{
    
}

pb::Uid AiSystem::GetType() const
{
    return GetStaticType();
}

pb::Uid AiSystem::GetStaticType()
{
    return pb::TypeHash("AiSystem");
}

void AiSystem::Update(pb::Scene* scene, float time)
{
    static_cast<World*>(scene)->GetPlayerAiDefinition().Devolve(time);
}
