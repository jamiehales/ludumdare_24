#include "pixelboost/logic/component/transform.h"

template <class T> bool World::FindClosestTarget(glm::vec3 position, glm::vec3& target)
{
    EntityMap entities = GetEntitiesByType<T>();
    
    bool status = false;
    float maxDistance = 10000.f;
    for (pb::Scene::EntityMap::iterator it = entities.begin(); it != entities.end(); ++it)
    {
        pb::TransformComponent* entityTransform = it->second->GetComponentByType<pb::TransformComponent>();
        float distance = glm::distance(entityTransform->GetPosition(), position);
        if (distance < maxDistance)
        {
            target = entityTransform->GetPosition();
            maxDistance = distance;
            status = true;
        } else if (distance == maxDistance)
        {
            if (rand()%2 == 0)
            {
                target = entityTransform->GetPosition();
                maxDistance = distance;
                status = true;
            }
        }
    }
    
    return status;
}
