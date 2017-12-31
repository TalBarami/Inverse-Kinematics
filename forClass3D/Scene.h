#pragma once
#include "GLFW/glfw3.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Scene
{
public:
	Scene();
	~Scene();
	
	void rotate(float angle, glm::vec3 direction);
	glm::mat4 rotation;
};

