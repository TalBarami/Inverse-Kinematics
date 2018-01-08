#include "Cube.h"
#include <glm/gtx/euler_angles.inl>


Cube::Cube()
{
	translates = glm::mat4(1);

	rotates = glm::mat4(1);
	angles = glm::vec3(0);

	ikRotates = glm::mat4(1);
	ikAngles = glm::vec3(0);

	limit = std::numeric_limits<float>::max();
}

void Cube::translate(glm::vec3 direction)
{
	translates = glm::translate(direction) * translates;
}

void Cube::rotate(float rx, float rz)
{
	rx = glm::radians(rx);
	rz = glm::radians(rz);
	if(rx != 0.0f && abs(angles.x + rx) > limit)
	{
		return;
	}
	angles.x += rx;
	angles.z += rz;

	auto eulerX = glm::eulerAngleX(angles.x);
	auto eulerZ = glm::eulerAngleZ(angles.z);
	rotates = eulerZ * eulerX;
}

void Cube::rotate(float angle, glm::vec3 direction)
{
	if (direction.x != 0.0f && abs(angles.x + angle) > limit)
	{
		return;
	}
	ikRotates = glm::rotate(angle, direction) * ikRotates;

	ikAngles += (direction * glm::radians(angle));
}

void Cube::reset()
{
	translates = glm::mat4(1);

	rotates = glm::mat4(1);
	angles = glm::vec3(0);

	ikRotates = glm::mat4(1);
	ikAngles = glm::vec3(0);
}

void Cube::setLimit(float limit)
{
	this->limit = glm::radians(limit);
}

Cube::~Cube()
{
}
