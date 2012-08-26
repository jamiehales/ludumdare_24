#include "glm/gtc/matrix_transform.hpp"

#include "pixelboost/logic/component/graphics/font.h"
#include "pixelboost/logic/component/input/rectTouch.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/input/touch.h"

#include "game/game.h"
#include "menu/startButton.h"

MenuStartButton::MenuStartButton(pb::Scene* scene)
    : pb::Entity(scene, 0)
{
    new pb::BasicTransformComponent(this);
    
    pb::FontComponent* title = new pb::FontComponent(this, "earthman", "HiveMind: EVOLUTION");
    title->SetSize(2.f);
    title->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,8.f,0)));
    
    pb::FontComponent* start = new pb::FontComponent(this, "earthman", "Click anywhere to start");
    start->SetSize(1.f);
    start->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,7.f,0)));
    
    pb::FontComponent* instructionsTitle = new pb::FontComponent(this, "earthman", "INSTRUCTIONS");
    instructionsTitle->SetSize(1.f);
    instructionsTitle->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,4.f,0)));
    
    pb::FontComponent* instructionsText = new pb::FontComponent(this, "earthman", "You're an alien race invading the well defended planet Kathulog.\nYour invading forces are quite advanced however and have the ability to evolve.\nSacrificing one of your own ships by clicking on it will encourage the hive mind\nof your queen ships to produce ships closer to that specification.\nThe produced ships are randomly mutated over time.\n\nMutated parameters are:\nDefense: The larger the surrounding orb, the more health your ships have.\nFire Power: The longer the projectiles, the higher power they are.\nFire Rate: Ships will fire faster.\n\nTIP: Be quick. The start game is very important if you don't want to get overwhelmed.");
    instructionsText->SetSize(1.f);
    instructionsText->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,2.f,0)));
    
    pb::RectTouchComponent* touch = new pb::RectTouchComponent(this);
    touch->SetSize(glm::vec2(20.f, 20.f));
    
    RegisterMessageHandler<pb::TouchDownMessage>(MessageHandler(this, &MenuStartButton::OnTouch));
}

MenuStartButton::~MenuStartButton()
{
    
}

pb::Uid MenuStartButton::GetType() const
{
    return MenuStartButton::GetStaticType();
}

pb::Uid MenuStartButton::GetStaticType()
{
    return pb::TypeHash("MenuStartButton");
}

void MenuStartButton::OnTouch(const pb::Message& message)
{
    Game::Instance()->Transition(Game::kGameModeGame);
}
