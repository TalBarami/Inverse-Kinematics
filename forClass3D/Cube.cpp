#include "Cube.h"



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

Cube::~Cube()
{
}
