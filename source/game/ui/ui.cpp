#include "glm/gtc/matrix_transform.hpp"

#include "pixelboost/logic/component/graphics/line.h"
#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/update.h"

#include "component/ai.h"
#include "game/ui/ui.h"
#include "game/world.h"

GameUi::GameUi(pb::Scene* scene, glm::vec3 position)
    : pb::Entity(scene, 0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetPosition(position);
    
    pb::RectangleComponent* defenseBar = new pb::RectangleComponent(this);
    defenseBar->SetSize(glm::vec2(10,0.5));
    defenseBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, 0.5, 0)));
    
    _DefenseIndicator = new pb::LineComponent(this);
    _DefenseIndicator->SetLine(glm::vec3(0,0.25,0), glm::vec3(0,-0.25,0));
    _DefenseIndicator->SetColor(glm::vec4(1,0,0,1));
    
    pb::RectangleComponent* speedBar = new pb::RectangleComponent(this);
    speedBar->SetSize(glm::vec2(10,0.5));
    speedBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, 0, 0)));
    
    _SpeedIndicator = new pb::LineComponent(this);
    _SpeedIndicator->SetLine(glm::vec3(0,0.25,0), glm::vec3(0,-0.25,0));
    _SpeedIndicator->SetColor(glm::vec4(0,0,1,1));
    
    pb::RectangleComponent* powerBar = new pb::RectangleComponent(this);
    powerBar->SetSize(glm::vec2(10,0.5));
    powerBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, -0.5, 0)));
    
    _PowerIndicator = new pb::LineComponent(this);
    _PowerIndicator->SetLine(glm::vec3(0,0.25,0), glm::vec3(0,-0.25,0));
    _PowerIndicator->SetColor(glm::vec4(0,1,0,1));
    
    pb::RectangleComponent* avoidanceBar = new pb::RectangleComponent(this);
    avoidanceBar->SetSize(glm::vec2(10,0.5));
    avoidanceBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, -1.0, 0)));
    
    _AvoidanceIndicator = new pb::LineComponent(this);
    _AvoidanceIndicator->SetLine(glm::vec3(0,0.25,0), glm::vec3(0,-0.25,0));
    _AvoidanceIndicator->SetColor(glm::vec4(1,1,0,1));
    
    RegisterMessageHandler<pb::UpdateMessage>(pb::Entity::MessageHandler(this, &GameUi::OnUpdate));
}

GameUi::~GameUi()
{
    UnregisterMessageHandler<pb::UpdateMessage>(pb::Entity::MessageHandler(this, &GameUi::OnUpdate));
}

pb::Uid GameUi::GetType() const
{
    return GameUi::GetStaticType();
}

pb::Uid GameUi::GetStaticType()
{
    return pb::TypeHash("GameUi");
}

void GameUi::OnUpdate(const pb::Message& message)
{
    AiDefinition& definition = static_cast<World*>(GetScene())->GetPlayerAiDefinition();
    
    _DefenseIndicator->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(-5.f + definition.Defense * 5.f, 0.5f, 0.f)));
    _SpeedIndicator->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(-5.f + definition.Speed * 5.f, 0.f, 0.f)));
    _PowerIndicator->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(-5.f + definition.Power * 5.f, -0.5f, 0.f)));
    _AvoidanceIndicator->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(-5.f + definition.Avoidance * 5.f, -1.f, 0.f)));
}
