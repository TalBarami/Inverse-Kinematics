#pragma once   //maybe should be static class
#include "GLFW/glfw3.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;

static const int ARRAY_LENGTH = 1 + 4;
static const int CUBE_SIZE = 2;
static const glm::vec3 SCALE_FACTOR = glm::vec3(1.0f, 1.0f, 2.0f);
static const float AXIS_LENGTH = 4.0f;
static const float ROTATION_ANGLE = 1.0f;

glm::mat4* cubes;
glm::vec3* colors;
glm::mat4 M, P, MVP, sceneX, sceneZ;

int selected = -1;

Vertex vertices[] =
{
	Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
	Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
	Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
	Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),

	Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),
	Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),
	Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),
	Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),glm::vec3(0, 0, 1)),

	Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
	Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
	Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
	Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),

	Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
	Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
	Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),
	Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),glm::vec3(0, 1, 0)),

	Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
	Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
	Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
	Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),

	Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0)),
	Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0)),
	Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0)),
	Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 0))
};

unsigned int indices[] = { 0, 1, 2,
0, 2, 3,

6, 5, 4,
7, 6, 4,

10, 9, 8,
11, 10, 8,

12, 13, 14,
12, 14, 15,

16, 17, 18,
16, 18, 19,

22, 21, 20,
23, 22, 20
};

Display display (DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
Shader shader("./res/shaders/basicShader");
Shader colorpickShader("./res/shaders/colorpickShader");
Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

inline void drawLine(glm::vec3 p1, glm::vec3 p2)
{
	glLineWidth(1);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
}

inline void rotateX(float direction)
{
	if(selected == -1)
	{
		sceneX = glm::rotate(5.0f, direction * vec3(1.0f, 0.0f, 0.0f)) * sceneX;
	} else
	{
		cubes[selected] = glm::rotate(5.0f, direction * vec3(1.0f, 0.0f, 0.0f)) * cubes[selected];
	}
}

inline void rotateZ(float direction)
{
	if(selected == -1)
	{
		sceneZ = glm::rotate(5.0f, direction * vec3(0.0f, 0.0f, 1.0f)) * sceneZ;
	} else
	{
		cubes[selected] = glm::rotate(5.0f, direction * vec3(0.0f, 0.0f, 1.0f)) * cubes[selected];
	}
}


inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS && action != GLFW_REPEAT)
	{
		return;
	}

	std::cout << "key_callback with: key=" << key << " scancode=" << scancode << " action=" << action << " mods=" << mods << std::endl;
	switch (key)
	{
	case GLFW_KEY_UP:
		rotateX(1.0f);
		break;
	case GLFW_KEY_DOWN:
		rotateX(-1.0f);
		break;
	case GLFW_KEY_RIGHT:
		rotateZ(1.0f);
		break;
	case GLFW_KEY_LEFT:
		rotateZ(-1.0f);
		break;
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	default:
		break;
	}
}

inline void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button != GLFW_MOUSE_BUTTON_LEFT || action != GLFW_PRESS)
	{
		return;
	}

	display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
	colorpickShader.Bind();

	for (auto i = 0; i < ARRAY_LENGTH; i++)
	{
		M = sceneX * sceneZ * cubes[i];
		MVP = P*M;
		colorpickShader.Update(MVP, M, colors[i]);
		mesh.Draw();
	}

	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);
	yPos = DISPLAY_HEIGHT - yPos;
	std::cout << "Cursor Position at (" << xPos << " : " << yPos << ")" << std::endl;

	glm::vec3 color;
	glReadPixels(xPos, yPos, 1, 1, GL_RGB, GL_FLOAT, &color);
	std::cout << "Color: (" << color.r << ", " << color.g << ", " << color.b << ")" << std::endl;

	auto selection = false;
	for (auto i = 0; i < ARRAY_LENGTH && !selection; i++)
	{
		if (colors[i] == color)
		{
			selected = i;
			std::cout << "Selected: " << selected << std::endl;
			selection = true;
		}
	}
	if(!selection)
	{
		selected = -1;
		std::cout << "No selection performed." << std::endl;
	}
}