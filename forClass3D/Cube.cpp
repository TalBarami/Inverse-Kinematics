#include "Cube.h"
#include <glm/gtx/euler_angles.inl>


Cube::Cube()
{
	translates = glm::mat4(1);
	rotates = glm::mat4(1);
	angles = glm::vec3(0);

	rotates_pick = glm::mat4(1);
}

void Cube::translate(glm::vec3 direction)
{
	translates = glm::translate(direction) * translates;
}

void Cube::rotate(float angle, glm::vec3 direction)
{
	rotates = glm::rotate(angle, direction) * rotates;
	angles.x += angle * direction.x;
	angles.y += angle * direction.y;
	angles.z += angle * direction.z;
	rotates_pick = rotates;
}

void Cube::rotate(float theta)
{
	auto eulerX = glm::eulerAngleX(theta);
	auto eulerZ = glm::eulerAngleZ(theta);

	rotates = eulerX * eulerZ * rotates_pick;
}

Cube::~Cube()
{
}
