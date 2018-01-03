#include "Cube.h"
#include <glm/gtx/euler_angles.inl>
#include <iostream>


Cube::Cube()
{
	translates = glm::mat4(1);
	rotates = glm::mat4(1);

	angles = glm::vec3(0);
	limit = std::numeric_limits<float>::max();
}

void Cube::translate(glm::vec3 direction)
{
	translates = glm::translate(direction) * translates;
}

void Cube::rotate(float angle, glm::vec3 direction)
{
	angle = glm::radians(angle);
	if (direction.x > 0.0f && abs(angles.x) > limit && angles.x * angle > 0.0f)
	{
		return;
	}
	angles += (direction * angle);

	auto eulerX = glm::eulerAngleX(angle * direction.x);
	auto eulerZ = glm::eulerAngleZ(angle * direction.z);
	rotates = eulerZ * eulerX * rotates;
}

void Cube::rotate(float rx, float rz)
{
	rx = glm::radians(rx);
	rz = glm::radians(rz);
	std::cout << "ang.x=" << angles.x  << " rx=" << rx << " lim=" << limit << std::endl;
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

void Cube::setLimit(float limit)
{
	this->limit = glm::radians(limit);
}

Cube::~Cube()
{
}
