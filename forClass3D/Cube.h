#pragma once
#include <glm/gtx/transform.hpp>
#include <string>

class Cube
{
public:
	Cube();
	~Cube();

	void translate(glm::vec3 direction);
	void position(glm::vec3 direction);
	void rotate(float rx, float ry);
	void rotate(float angle, glm::vec3 direction);
	void reset();

	void setLimit(float limit);

	glm::mat4 translates;
	glm::mat4 M;

	glm::mat4 rotates;
	glm::vec3 angles;

	glm::mat4 ikRotates;

	glm::vec3 color;

	float limit;
};

