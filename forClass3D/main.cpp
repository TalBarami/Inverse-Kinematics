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
	P = glm::perspective(60.0f, float(DISPLAY_WIDTH) / float(DISPLAY_HEIGHT), 0.1f, 100.0f);
	P = P * glm::lookAt(pos, pos + forward, up);

	chain = new Cube[ARRAY_LENGTH];

	box.translate(vec3(5.0f, 0.0f, 0.0f));
	box.rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
	box.color = vec3(1.0f, 0.0f, 0.0f);

	for (auto i = 0; i < ARRAY_LENGTH; i++)
	{
		chain[i].color = vec3(float(i) / 255.0f, 1.0f, 1.0f);
	}

	glfwSetKeyCallback(display.m_window,key_callback);
	glfwSetMouseButtonCallback(display.m_window, mouse_callback);
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




