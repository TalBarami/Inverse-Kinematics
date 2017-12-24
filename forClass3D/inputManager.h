#pragma once   //maybe should be static class
#include "GLFW\glfw3.h"
static const int CUBE_SIZE = 2;
static const glm::vec3 SCALE_FACTOR = glm::vec3(1, 1, 2);
static const float DELTA = 1.1;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			if(action == GLFW_PRESS)
				glfwSetWindowShouldClose(window,GLFW_TRUE);
			break;
		default:
			break;
		}
		
	}



