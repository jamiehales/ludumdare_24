#include "game/enemy/site.h"

Site::Site(pb::Scene* scene)
    : pb::Entity(scene, 0)
{
    
}

Site::~Site()
{
    
}

pb::Uid Site::GetType() const
{
    return Site::GetStaticType();
}

pb::Uid Site::GetStaticType()
{
    return pb::TypeHash("Site");
}
