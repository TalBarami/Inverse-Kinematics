#pragma once   //maybe should be static class
#include "GLFW/glfw3.h"
#include "Cube.h"
#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;

static const int ARRAY_LENGTH = 4;
static const int CUBE_SIZE = 2;
static const glm::vec3 SCALE_FACTOR = glm::vec3(1.0f, 1.0f, 2.0f);
static const float AXIS_LENGTH = 4.0f;
static const float ROTATION_ANGLE = 1.0f;
static const float PI = 3.1415;

Cube* chain;
Cube box;
Scene scene;
glm::mat4 M, N, P, MVP;

bool rotateMouse;
bool translateMouse;
double clickX, clickY;

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

unsigned int indices[] = { 
	0, 1, 2,
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
	auto xRotation = vec3(1.0f, 0.0f, 0.0f);
	auto rotation = direction * 5.0f;
	if(selected == -1)
	{
		scene.rotate(rotation, xRotation);
	}
	else if (abs(chain[selected].angles.x) < 45.0f || chain[selected].angles.x * direction <= 0)
	{
		chain[selected].rotate(rotation, xRotation);
	}
}

inline void rotateY(float direction)
{
	auto yRotation = vec3(0.0f, 1.0f, 0.0f);
	auto rotation = direction * 5.0f;
	if (selected == -1)
	{
		scene.rotate(rotation, yRotation);
	}
	else if (abs(chain[selected].angles.y) < 45.0f || chain[selected].angles.y * direction <= 0)
	{
		chain[selected].rotate(rotation, yRotation);
	}
}


inline void rotateZ(float direction)
{
	auto zRotation = vec3(0.0f, 0.0f, 1.0f);
	auto rotation = direction * 5.0f;
	if (selected == -1)
	{
		scene.rotate(rotation, zRotation);
	}
	else //if (abs(chain[selected].angles.z) < 45.0f || chain[selected].angles.z * direction <= 0)
	{
		chain[selected].rotate(rotation, zRotation);
	}
}


inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "key_callback: key=" << key << " scancode=" << scancode << " action=" << action << " mods=" << mods << std::endl;
	if (action != GLFW_PRESS && action != GLFW_REPEAT)
	{
		return;
	}
	switch (key)
	{
	case GLFW_KEY_UP:
		rotateX(1.0f);
		break;
	case GLFW_KEY_DOWN:
		rotateX(-1.0f);
		break;
	case GLFW_KEY_RIGHT:
		rotateZ(-1.0f);
		break;
	case GLFW_KEY_LEFT:
		rotateZ(1.0f);
		break;
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	default:
		break;
	}
}

inline void translateToMouse()
{
	double x2, y2;
	glfwGetCursorPos(display.m_window, &x2, &y2);
	y2 = DISPLAY_HEIGHT - y2;

	auto dst = vec3(clickX - x2, 0.0f, DISPLAY_HEIGHT - (clickY - y2));
	dst /= 1000;
	if (selected == ARRAY_LENGTH)
	{
		box.translate(dst);
	}
	else if (selected >= 0)
	{
		chain[0].translate(dst);
	}
	clickX = x2;
	clickY = y2;
}

inline void rotateToMouse()
{
	double x2, y2;
	glfwGetCursorPos(display.m_window, &x2, &y2);

	float dx = clickX - x2;
	float dy = clickY - y2;
	auto theta = atan(dy / dx);

	if (selected == ARRAY_LENGTH)
	{
		box.rotate(theta);
	}
	else if(selected >= 0)
	{
		chain[selected].rotate(theta);
	}
}

inline void drawScene(Shader& shader, bool drawAxis)
{
	display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
	shader.Bind();

	if(translateMouse)
	{
		translateToMouse();
	}
	if(rotateMouse)
	{
		rotateToMouse();
	}

	M = scene.rotation * box.rotates * box.translates;
	MVP = P * M;
	shader.Update(MVP, M, box.color);
	mesh.Draw();

	for (auto i = 0; i < ARRAY_LENGTH; i++)
	{
		if (i == 0)
		{
			M = scene.rotation * chain[i].rotates * chain[i].translates;
			M = glm::scale(SCALE_FACTOR) * M;
			M = glm::rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f)) * M;
		}
		else
		{
			M = N * glm::translate(vec3(0, 0, 1)) * chain[i].rotates * chain[i].translates * glm::translate(vec3(0, 0, 1));
		}
		N = M;
		MVP = P * M;
		shader.Update(MVP, M, chain[i].color);
		mesh.Draw();

		if(drawAxis)
		{
			drawLine(vec3(float(AXIS_LENGTH), 0.0f, -1.0f), vec3(-float(AXIS_LENGTH), 0.0f, -1.0f));
			drawLine(vec3(0.0f, 0.0f, float(AXIS_LENGTH)), vec3(0.0f, 0.0f, -float(AXIS_LENGTH)));
		}
	}
}

inline void pick(float xPos, float yPos)
{
	glm::vec3 color;
	glReadPixels(xPos, yPos, 1, 1, GL_RGB, GL_FLOAT, &color);
	std::cout << "Color: (" << color.r << ", " << color.g << ", " << color.b << ")" << std::endl;

	auto selection = false;
	if (box.color == color)
	{
		selected = ARRAY_LENGTH;
		std::cout << "Selected: " << selected << std::endl;
		selection = true;
	}
	for (auto i = 0; i < ARRAY_LENGTH && !selection; i++)
	{
		if (chain[i].color == color)
		{
			selected = i;
			std::cout << "Selected: " << selected << std::endl;
			selection = true;
		}
	}
	if (!selection)
	{
		selected = -1;
		std::cout << "No selection performed." << std::endl;
	}
}

inline void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	std::cout << "mouse_callback: button=" << button << ", action=" << action << ", mods=" << mods << std::endl;

	glfwGetCursorPos(window, &clickX, &clickY);
	clickY = DISPLAY_HEIGHT - clickY;
	std::cout << "Cursor Position at (" << clickX << " : " << clickY << ")" << std::endl;

	if(action == GLFW_PRESS)
	{
		drawScene(colorpickShader, false);
		pick(clickX, clickY);
	}

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		switch (action)
		{
		case GLFW_PRESS:
			rotateMouse = selected != -1;
			break;
		case GLFW_RELEASE:
			rotateMouse = false;
			break;
		default:
			break;
		}
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		switch (action)
		{
		case GLFW_PRESS:
			translateMouse = selected != -1;
			break;
		case GLFW_RELEASE:
			translateMouse = false;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

inline void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	std::cout << "scroll_callback: xOffset=" << xOffset << ", yOffset=" << yOffset << std::endl;
	auto dst = vec3(0.0f, yOffset, 0.0f);
	if (selected == ARRAY_LENGTH)
	{
		box.translate(dst);
	}
	else if (selected >= 0)
	{
		chain[0].translate(dst);
	}
}