#include "glm/gtc/matrix_transform.hpp"

#include "pixelboost/logic/component/graphics/sprite.h"
#include "pixelboost/logic/component/input/rectTouch.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/input/touch.h"

#include "game/game.h"
#include "menu/start.h"

MenuStart::MenuStart(pb::Scene* scene)
    : pb::Entity(scene, 0)
{
    new pb::BasicTransformComponent(this);
    
    pb::SpriteComponent* sprite = new pb::SpriteComponent(this, "difficulty");
    glm::mat4x4 transform = glm::translate(glm::mat4x4(), glm::vec3(0,-9.5,0));
    transform = glm::scale(transform, glm::vec3(0.8,0.8,1));
    sprite->SetLocalTransform(transform);
    
    _EasyTouch = new pb::RectTouchComponent(this);
    _EasyTouch->SetSize(glm::vec2(5.f, 5.f));
    _EasyTouch->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(-5.f,-9.5,0)));
    
    _MediumTouch = new pb::RectTouchComponent(this);
    _MediumTouch->SetSize(glm::vec2(5.f, 5.f));
    _MediumTouch->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0.f,-9.5,0)));
    
    _HardTouch = new pb::RectTouchComponent(this);
    _HardTouch->SetSize(glm::vec2(5.f, 5.f));
    _HardTouch->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(5.f,-9.5,0)));
    
    RegisterMessageHandler<pb::TouchDownMessage>(MessageHandler(this, &MenuStart::OnTouch));
}

MenuStart::~MenuStart()
{
    
}

pb::Uid MenuStart::GetType() const
{
    return MenuStart::GetStaticType();
}

pb::Uid MenuStart::GetStaticType()
{
    return pb::TypeHash("MenuStart");
}

void MenuStart::OnTouch(const pb::Message& message)
{
    if (message.GetComponent() == _EasyTouch)
        Game::Instance()->Transition(Game::kGameModeGame, 0);
    else if (message.GetComponent() == _MediumTouch)
        Game::Instance()->Transition(Game::kGameModeGame, 1);
    else if (message.GetComponent() == _HardTouch)
        Game::Instance()->Transition(Game::kGameModeGame, 2);
}
