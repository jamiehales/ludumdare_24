#include "pixelboost/logic/component/graphics/ellipse.h"
#include "pixelboost/logic/component/transform/basic.h"
#include "pixelboost/logic/message/update.h"

#include "game/explosion.h"

Explosion::Explosion(pb::Scene* scene, glm::vec3 position)
    : pb::Entity(scene, 0)
    , _Time(0)
{
    pb::TransformComponent* transform = new pb::BasicTransformComponent(this);
    transform->SetPosition(glm::vec3(position.x, position.y, 0.f));
    
    pb::EllipseComponent* ellipse = new pb::EllipseComponent(this);
    ellipse->SetSize(glm::vec2(0.f, 0.f));
    ellipse->SetColor(glm::vec4(1,1,1,1));
    ellipse->SetSolid(true);
    
    RegisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Explosion::OnUpdate));
}

Explosion::~Explosion()
{
    UnregisterMessageHandler<pb::UpdateMessage>(MessageHandler(this, &Explosion::OnUpdate));
}

pb::Uid Explosion::GetType() const
{
    return Explosion::GetStaticType();
}

pb::Uid Explosion::GetStaticType()
{
    return pb::TypeHash("Explosion");
}

void Explosion::OnUpdate(const pb::Message& message)
{
    float deathTime = 0.4f;
    
    const pb::UpdateMessage& updateMessage = static_cast<const pb::UpdateMessage&>(message);
    _Time += updateMessage.GetDelta();
    
    pb::EllipseComponent* ellipse = GetComponentByType<pb::EllipseComponent>();
    ellipse->SetSize(glm::vec2(1.f, 1.f)*(_Time*(3.f/deathTime)));
    ellipse->SetColor(glm::vec4(1,1,1,(1.f-(_Time/deathTime))*2.f));
    
    if (_Time > deathTime)
    {
        Destroy();
    }
}
