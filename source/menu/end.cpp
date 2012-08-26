#include "glm/gtc/matrix_transform.hpp"

#include "pixelboost/logic/component/graphics/font.h"
#include "pixelboost/logic/component/input/rectTouch.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/input/touch.h"

#include "game/game.h"
#include "menu/end.h"

EndInfo::EndInfo(pb::Scene* scene, bool success)
    : pb::Entity(scene, 0)
{
    new pb::BasicTransformComponent(this);
    
    pb::FontComponent* game = new pb::FontComponent(this, "earthman", "HiveMind: EVOLUTION");
    game->SetSize(2.f);
    game->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,10.f,0)));
    
    pb::FontComponent* title = new pb::FontComponent(this, "earthman", success ? "YOU WON!" : "YOU LOST!");
    title->SetSize(1.f);
    title->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,8.f,0)));
    
    pb::FontComponent* details = new pb::FontComponent(this, "earthman", success ? "Those Kathulogians are toast, congratulations!" : "Their defenses were more than you could handle, why don't you try again?");
    details->SetSize(1.f);
    details->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,6.f,0)));
    
    pb::FontComponent* instructions = new pb::FontComponent(this, "earthman", "Click anywhere to return to the menu");
    instructions->SetSize(1.f);
    instructions->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0,-10.f,0)));

    pb::RectTouchComponent* touch = new pb::RectTouchComponent(this);
    touch->SetSize(glm::vec2(20.f, 20.f));
    
    RegisterMessageHandler<pb::TouchDownMessage>(MessageHandler(this, &EndInfo::OnTouch));
}

EndInfo::~EndInfo()
{
    UnregisterMessageHandler<pb::TouchDownMessage>(MessageHandler(this, &EndInfo::OnTouch));
}

pb::Uid EndInfo::GetType() const
{
    return EndInfo::GetStaticType();
}

pb::Uid EndInfo::GetStaticType()
{
    return pb::TypeHash("MenuTitle");
}

void EndInfo::OnTouch(const pb::Message& message)
{
    Game::Instance()->Transition(Game::kGameModeMenu);
}
