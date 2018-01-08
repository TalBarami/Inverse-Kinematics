#include <Windows.h>
#include <iostream>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "inputManager.h"

using namespace glm;


int main(int argc, char** argv)
{
	auto pos = -vec3(0.0f, 0.0f, 8.0f * ARRAY_LENGTH);
	auto forward = glm::vec3(0.0f, 0.0f, 1.0f);
	auto up = glm::vec3(0.0f, 1.0f, 0.0f);
	P = glm::perspective(CAM_ANGLE, float(DISPLAY_WIDTH) / float(DISPLAY_HEIGHT), pNEAR, pFAR);
	P = P * glm::lookAt(pos, pos + forward, up);

	ikSolver = false;
	rotateMouse = false;
	translateMouse = false;

	chain = new Cube[ARRAY_LENGTH + 1];

	chain[ARRAY_LENGTH].translate(vec3(5.0f, 0.0f, 0.0f));
	chain[ARRAY_LENGTH].color = vec3(1.0f, 0.0f, 0.0f);

	for (auto i = 0; i < ARRAY_LENGTH; i++)
	{
		chain[i].color = vec3(float(i) / 255.0f, 1.0f, 1.0f);
		chain[i].setLimit(ROTATION_LIMIT);
	}

	glfwSetKeyCallback(display.m_window,key_callback);
	glfwSetMouseButtonCallback(display.m_window, mouse_callback);
	glfwSetCursorPosCallback(display.m_window, cursor_position_callback);
	glfwSetScrollCallback(display.m_window, scroll_callback);

	while(!glfwWindowShouldClose(display.m_window))
	{
		Sleep(3);
		drawScene(shader, true);
		display.SwapBuffers();
		glfwPollEvents();
	}

	return 0;
}




