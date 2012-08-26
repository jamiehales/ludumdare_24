#include "glm/gtc/matrix_transform.hpp"

#include "pixelboost/logic/component/graphics/sprite.h"
#include "pixelboost/logic/component/transform/basic.h"

#include "game/planet.h"

Planet::Planet(pb::Scene* scene)
    : pb::Entity(scene, 0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetPosition(glm::vec3(0,0,-5));
    
    pb::SpriteComponent* sprite = new pb::SpriteComponent(this, "planet");
    sprite->SetLocalTransform(glm::scale(glm::mat4x4(), glm::vec3(0.55,0.55,1)));
}

Planet::~Planet()
{
    
}

pb::Uid Planet::GetType() const
{
    return Planet::GetStaticType();
}

pb::Uid Planet::GetStaticType()
{
    return pb::TypeHash("Planet");
}
