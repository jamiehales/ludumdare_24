#include "glm/gtx/random.hpp"

#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/component/physics/2d/userBody.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/physics/collision.h"
#include "pixelboost/logic/message/update.h"
#include "pixelboost/logic/scene.h"

#include "component/ai.h"
#include "component/health.h"
#include "component/target.h"
#include "game/enemy/enemy.h"
#include "game/player/queen.h"
#include "game/player/ship.h"
#include "game/projectiles/bullet.h"
#include "game/world.h"
#include "message/target.h"

Enemy::Enemy(pb::Scene* scene, const AiDefinition& definition, glm::vec3 position, float rotation)
    : pb::Entity(scene, 0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(position, glm::vec3(0,0,rotation), glm::vec3(1,1,1));
    
    pb::RectangleComponent* ellipse = new pb::RectangleComponent(this);
    ellipse->SetSize(glm::vec2(0.15,0.25));
    ellipse->SetSolid(true);
    ellipse->SetColor(glm::vec4(0.8,0,0,1));
    
    glm::vec3 target;
    static_cast<World*>(scene)->FindClosestTarget<Queen>(transform->GetPosition(), target);
    target += glm::vec3(glm::compRand1(-5.f,5.f), glm::compRand1(-5.f,5.f),0.f);
    
    new TargetingComponent(this, 0.2f);
    GetScene()->SendMessage(GetUid(), TargetMessage(this, 0, target));
    
    new HealthComponent(this, HealthComponent::kHealthTypeEnemy, 2.f, 1.f);
    
    new AiComponent(this, AiComponent::kAiTypeEnemy, definition);
    
    pb::PhysicsUserBody2DComponent* physics = new pb::PhysicsUserBody2DComponent(this, pb::PhysicsUserBody2DComponent::kBodyTypeDynamic, pb::PhysicsUserBody2DComponent::kBodyShapeRect, glm::vec2(0.15, 0.25)/*sprite->GetSize()*/);
    physics->SetSensor(true);
}

Enemy::~Enemy()
{

}

pb::Uid Enemy::GetType() const
{
    return Enemy::GetStaticType();
}

pb::Uid Enemy::GetStaticType()
{
    return pb::TypeHash("Enemy");
}
