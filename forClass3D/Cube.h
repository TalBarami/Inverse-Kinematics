#pragma once
#include "GLFW/glfw3.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Cube
{
public:
	Cube();
	~Cube();

	void translate(glm::vec3 direction);
	void rotate(float rx, float ry);

	void setLimit(float limit);

	glm::mat4 translates;
	glm::mat4 rotates;
	glm::vec3 color;

private:
	glm::vec3 angles;
	float limit;
	void rotate(float angle, glm::vec3 direction);
};

