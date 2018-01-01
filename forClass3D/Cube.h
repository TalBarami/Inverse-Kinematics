#pragma once
#include "GLFW/glfw3.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Cube
{
public:
	Cube();
	~Cube();

	void rotate(float angle, glm::vec3 direction);
	void translate(glm::vec3 direction);

	glm::mat4 translates;
	glm::mat4 rotates;
	glm::vec3 angles;
	glm::vec3 color;
	glm::mat4 rotates_pick;
};

