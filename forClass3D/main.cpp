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

	cubes = new glm::mat4[ARRAY_LENGTH];
	colors = new glm::vec3[ARRAY_LENGTH];
	sceneX = mat4(1);
	sceneZ = mat4(1);

	cubes[0] = mat4(1);
	cubes[0] = glm::translate(vec3(5.0f, 0.0f, 0.0f)) * cubes[0];
	cubes[0] = glm::rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f)) * cubes[0];
	colors[0] = glm::vec3(0.0f, 1.0f, 1.0f);

	for (auto i = 1; i < ARRAY_LENGTH; i++)
	{
		cubes[i] = mat4(1);
		cubes[i] = glm::translate(vec3(0, 0, SCALE_FACTOR.z) * float(i-1) * float(CUBE_SIZE)) * cubes[i];
		cubes[i] = glm::rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f)) * cubes[i];
		cubes[i] = glm::scale(cubes[i], SCALE_FACTOR);

		colors[i] = glm::vec3(float(i) / 255.0f, 1.0f, 1.0f);
	}

	glfwSetKeyCallback(display.m_window,key_callback);
	glfwSetMouseButtonCallback(display.m_window, mouse_callback);

	while(!glfwWindowShouldClose(display.m_window))
	{
		Sleep(3);
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
		shader.Bind();

		for (auto i = 0; i < ARRAY_LENGTH; i++)
		{
			M = sceneX * sceneZ * /*cubes[i-1] * */ cubes[i];
			MVP = P * M;
			shader.Update(MVP, M, colors[i]);
			mesh.Draw();

			drawLine(vec3(float(AXIS_LENGTH), 0.0f, -1.0f), vec3(-float(AXIS_LENGTH), 0.0f, -1.0f));
			drawLine(vec3(0.0f, 0.0f, float(AXIS_LENGTH)), vec3(0.0f, 0.0f, -float(AXIS_LENGTH)));
		}

		display.SwapBuffers();
		glfwPollEvents();
	}

	return 0;
}




