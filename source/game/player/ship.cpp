#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/random.hpp"

#include "pixelboost/logic/component/graphics/sprite.h"
#include "pixelboost/logic/component/input/rectTouch.h"
#include "pixelboost/logic/component/physics/2d/userBody.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/input/touch.h"
#include "pixelboost/logic/system/debug/render.h"
#include "pixelboost/logic/scene.h"

#include "component/ai.h"
#include "component/health.h"
#include "component/target.h"
#include "game/enemy/site/spawner.h"
#include "game/enemy/enemy.h"
#include "game/player/queen.h"
#include "game/player/ship.h"
#include "game/projectiles/bullet.h"
#include "game/explosion.h"
#include "game/world.h"
#include "message/target.h"

Ship::Ship(pb::Scene* scene, const AiDefinition& definition, glm::vec3 position, float rotation)
    : pb::Entity(scene, 0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(position, glm::vec3(0,0,rotation), glm::vec3(1,1,1));
    
    pb::SpriteComponent* sprite = new pb::SpriteComponent(this, "ship");
    sprite->SetLocalTransform(glm::scale(glm::mat4x4(), glm::vec3(1,1,1)*0.25f));
    
    pb::RectTouchComponent* touch = new pb::RectTouchComponent(this);
    touch->SetSize(glm::vec2(0.7f, 0.7f));
    
    glm::vec3 target;
    static_cast<World*>(GetScene())->FindClosestTarget<SpawnerSite>(transform->GetPosition(), target);
    target += glm::vec3(glm::compRand1(-5.f,5.f), glm::compRand1(-5.f,5.f),0.f);
    
    pb::PhysicsUserBody2DComponent* physics = new pb::PhysicsUserBody2DComponent(this, pb::PhysicsUserBody2DComponent::kBodyTypeDynamic, pb::PhysicsUserBody2DComponent::kBodyShapeRect, sprite->GetSize() * 0.25f);
    physics->SetSensor(true);
    
    new TargetingComponent(this, 0.2f * definition.Speed);
    GetScene()->SendMessage(GetUid(), TargetMessage(this, 0, target));
    
    new HealthComponent(this, HealthComponent::kHealthTypePlayer, 2.f * definition.Defense, 1.f);
    
    new AiComponent(this, AiComponent::kAiTypePlayer, definition);
    
    RegisterMessageHandler<pb::TouchDownMessage>(MessageHandler(this, &Ship::OnTouch));
}

Ship::~Ship()
{
    UnregisterMessageHandler<pb::TouchDownMessage>(MessageHandler(this, &Ship::OnTouch));
}

pb::Uid Ship::GetType() const
{
    return Ship::GetStaticType();
}

pb::Uid Ship::GetStaticType()
{
    return pb::TypeHash("Ship");
}

void Ship::OnTouch(const pb::Message& message)
{
    AiComponent* aiComponent = GetComponentByType<AiComponent>();
    static_cast<World*>(GetScene())->GetPlayerAiDefinition().Adapt(aiComponent->GetDefinition());
    
    pb::TransformComponent* transform = GetComponentByType<pb::TransformComponent>();
    new Explosion(GetScene(), transform->GetPosition());
    Destroy();
}
