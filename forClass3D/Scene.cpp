#include "Scene.h"



Scene::Scene()
{
}

void Scene::rotate(float angle, glm::vec3 direction)
{
	rotation = glm::rotate(angle, direction) * rotation;
}

Scene::~Scene()
{
}
