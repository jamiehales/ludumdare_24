#include "glm/gtc/matrix_transform.hpp"

#include "pixelboost/logic/component/graphics/font.h"
#include "pixelboost/logic/component/input/rectTouch.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/input/touch.h"

#include "game/game.h"
#include "menu/title.h"

MenuTitle::MenuTitle(pb::Scene* scene)
    : pb::Entity(scene, 0)
{
    new pb::BasicTransformComponent(this);
    
    pb::FontComponent* title = new pb::FontComponent(this, "earthman", "HiveMind: EVOLUTION");
    title->SetSize(2.f);
    title->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,10.f,0)));
    
    pb::FontComponent* instructionsTitle = new pb::FontComponent(this, "earthman", "INSTRUCTIONS");
    instructionsTitle->SetSize(1.f);
    instructionsTitle->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,8.f,0)));
    
    pb::FontComponent* instructionsText = new pb::FontComponent(this, "earthman", "You're an alien race invading the well defended planet Kathulog.\nYour invading forces are quite weaker, but have the ability to evolve.\nSacrificing one of your own ships by clicking on it will encourage the hive mind\nof your queen ships to produce ships closer to that specification.\nThe produced ships are randomly mutated over time.\n\nMutated parameters are:\n   Defense    ~ The larger the surrounding orb, the more health your ships have.\n   Fire Power ~ The longer the projectiles, the higher power they are.\n   Fire Rate   ~ Ships will fire faster.\n\nTIPS: Be quick. The start game is very important if you don't want to get overwhelmed.\n      All difficulties are possible, you just have to use the right strategy.\n      Keep mutating, your ships slowly devolve over time.");
    instructionsText->SetSize(1.f);
    instructionsText->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,6.f,0)));
    
    pb::RectTouchComponent* touch = new pb::RectTouchComponent(this);
    touch->SetSize(glm::vec2(20.f, 20.f));
    
    RegisterMessageHandler<pb::TouchDownMessage>(MessageHandler(this, &MenuTitle::OnTouch));
}

MenuTitle::~MenuTitle()
{
    
}

pb::Uid MenuTitle::GetType() const
{
    return MenuTitle::GetStaticType();
}

pb::Uid MenuTitle::GetStaticType()
{
    return pb::TypeHash("MenuTitle");
}

void MenuTitle::OnTouch(const pb::Message& message)
{
    Game::Instance()->Transition(Game::kGameModeGame);
}
