#include "glm/gtc/matrix_transform.hpp"

#include "pixelboost/logic/component/graphics/font.h"
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
    defenseBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, 0.5, -1)));
    defenseBar->SetColor(glm::vec4(1,1,1,0.7));
    defenseBar->SetSolid(true);
    
    pb::FontComponent* defenseText = new pb::FontComponent(this, "earthman", "DEFENSE");
    defenseText->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(-5.1, 0.3, 0)));
    defenseText->SetAlignment(pb::kFontAlignRight);
    defenseText->SetSize(0.5);
    
    _DefenseIndicator = new pb::RectangleComponent(this);
    _DefenseIndicator->SetSize(glm::vec2(1,0.5));
    _DefenseIndicator->SetColor(glm::vec4(0,0,0,0.5));
    _DefenseIndicator->SetSolid(true);
    
    pb::RectangleComponent* speedBar = new pb::RectangleComponent(this);
    speedBar->SetSize(glm::vec2(10,0.5));
    speedBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, 0, -1)));
    speedBar->SetColor(glm::vec4(1,1,1,0.5));
    speedBar->SetSolid(true);
    
    pb::FontComponent* speedText = new pb::FontComponent(this, "earthman", "SPEED");
    speedText->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(-5.1, -0.2, 0)));
    speedText->SetAlignment(pb::kFontAlignRight);
    speedText->SetSize(0.5);
    
    _SpeedIndicator = new pb::RectangleComponent(this);
    _SpeedIndicator->SetSize(glm::vec2(1,0.5));
    _SpeedIndicator->SetColor(glm::vec4(0,0,0,0.5));
    _SpeedIndicator->SetSolid(true);
    
    pb::RectangleComponent* powerBar = new pb::RectangleComponent(this);
    powerBar->SetSize(glm::vec2(10,0.5));
    powerBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, -0.5, -1)));
    powerBar->SetColor(glm::vec4(1,1,1,0.7));
    powerBar->SetSolid(true);
    
    pb::FontComponent* powerText = new pb::FontComponent(this, "earthman", "POWER");
    powerText->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(-5.1, -0.7, 0)));
    powerText->SetAlignment(pb::kFontAlignRight);
    powerText->SetSize(0.5);
    
    _PowerIndicator = new pb::RectangleComponent(this);
    _PowerIndicator->SetSize(glm::vec2(1,0.5));
    _PowerIndicator->SetColor(glm::vec4(0,0,0,0.5));
    _PowerIndicator->SetSolid(true);
    
    pb::RectangleComponent* fireRateBar = new pb::RectangleComponent(this);
    fireRateBar->SetSize(glm::vec2(10,0.5));
    fireRateBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, -1.0, -1)));
    fireRateBar->SetColor(glm::vec4(1,1,1,0.5));
    fireRateBar->SetSolid(true);
    
    pb::FontComponent* fireRateText = new pb::FontComponent(this, "earthman", "FIRE RATE");
    fireRateText->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(-5.1, -1.2, 0)));
    fireRateText->SetAlignment(pb::kFontAlignRight);
    fireRateText->SetSize(0.5);
    
    _FireRateIndicator = new pb::RectangleComponent(this);
    _FireRateIndicator->SetSize(glm::vec2(1,0.5));
    _FireRateIndicator->SetColor(glm::vec4(0,0,0,0.5));
    _FireRateIndicator->SetSolid(true);
    
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

void GameUi::SetBarStatus(pb::RectangleComponent* rect, float value, float offset)
{
    glm::mat4x4 transform = glm::translate(glm::mat4x4(), glm::vec3((-5.f + value * 5.f) / 2.f, offset, 0.f));
    transform = glm::scale(transform, glm::vec3(5*glm::max(0.01f,glm::abs(value-1.f)),1,1));
    rect->SetLocalTransform(transform);
    
    float color = glm::min(1.f, 0.3f + glm::abs(value-1.0f));
    
    rect->SetColor(glm::vec4(value < 1.f ? color : 0.f, value > 1.f ? color : 0.f, 0.f, 1.f));
}

void GameUi::OnUpdate(const pb::Message& message)
{
    AiDefinition& definition = static_cast<World*>(GetScene())->GetPlayerAiDefinition();
    
    SetBarStatus(_DefenseIndicator, definition.Defense, 0.5f);
    SetBarStatus(_SpeedIndicator, definition.Speed, 0.0f);
    SetBarStatus(_PowerIndicator, definition.Power, -0.5f);
    SetBarStatus(_FireRateIndicator, definition.FireRate, -1.f);
}
