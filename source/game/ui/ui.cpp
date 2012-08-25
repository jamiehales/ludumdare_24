#include "glm/gtc/matrix_transform.hpp"

#include "pixelboost/logic/component/graphics/rectangle.h"
#include "pixelboost/logic/component/transform/basic.h"

#include "game/ui/ui.h"

GameUi::GameUi(pb::Scene* scene, glm::vec3 position)
    : pb::Entity(scene, 0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetPosition(position);
    
    pb::RectangleComponent* defenseBar = new pb::RectangleComponent(this);
    defenseBar->SetSize(glm::vec2(10,0.5));
    defenseBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, 0.5, 0)));
    
    pb::RectangleComponent* speedBar = new pb::RectangleComponent(this);
    speedBar->SetSize(glm::vec2(10,0.5));
    speedBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, 0, 0)));
    
    pb::RectangleComponent* powerBar = new pb::RectangleComponent(this);
    powerBar->SetSize(glm::vec2(10,0.5));
    powerBar->SetLocalTransform(glm::translate(glm::mat4x4(), glm::vec3(0, -0.5, 0)));
}

GameUi::~GameUi()
{
    
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
    
}
