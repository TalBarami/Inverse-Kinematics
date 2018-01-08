#include "Scene.h"
#include <glm/gtx/euler_angles.inl>


Scene::Scene()
{
	rotates = glm::mat4(1);
	angles = glm::vec3(0);
}

void Scene::rotate(float angle, glm::vec3 direction)
{
	rotates = glm::rotate(angle, direction) * rotates;
}

void Scene::rotate(float rx, float rz)
{
	rx = glm::radians(rx);
	rz = glm::radians(rz);

	angles.x += rx;
	angles.z += rz;

	auto eulerX = glm::eulerAngleX(angles.x);
	auto eulerZ = glm::eulerAngleZ(angles.z);
	rotates = eulerZ * eulerX;
}

void Scene::reset()
{
	rotates = glm::mat4(1);
	angles = glm::vec3(0);
}

Scene::~Scene()
{
}
