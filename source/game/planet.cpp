#include "pixelboost/logic/component/graphics/ellipse.h"
#include "pixelboost/logic/component/transform/basic.h"

#include "game/planet.h"

Planet::Planet(pb::Scene* scene)
    : pb::Entity(scene, 0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetPosition(glm::vec3(0,0,-5));
    
    pb::EllipseComponent* ellipse = new pb::EllipseComponent(this);
    ellipse->SetSize(glm::vec2(6,6));
    ellipse->SetSolid(true);
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
