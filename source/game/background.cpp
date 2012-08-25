#include "pixelboost/logic/component/graphics/sprite.h"
#include "pixelboost/logic/component/transform/basic.h"

#include "game/background.h"

Background::Background(pb::Scene* scene)
    : pb::Entity(scene, 0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetTransform(glm::vec3(0,0,-10), glm::vec3(0,0,0), glm::vec3(1,1,1));
    
    new pb::SpriteComponent(this, "background");
}

Background::~Background()
{
    
}

pb::Uid Background::GetType() const
{
    return Background::GetStaticType();
}

pb::Uid Background::GetStaticType()
{
    return pb::TypeHash("Background");
}
