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
static const float CAM_ANGLE = 60.0f;
static const float REL = float(DISPLAY_WIDTH) / float(DISPLAY_HEIGHT);
static const float pNEAR = 0.1f;
static const float pFAR = 100.0f;

static const int ARRAY_LENGTH = 4;
static const int CUBE_SIZE = 2;
static const glm::vec3 SCALE_FACTOR = glm::vec3(1.0f, 1.0f, 2.0f);
static const float AXIS_LENGTH = 4.0f;
static const float PI = 3.14159265359;

Cube* chain;
Scene scene;
glm::mat4 M, N, P, MVP;

bool rotateMouse;
bool translateMouse;
double prevX, prevY;
GLfloat depth[1];

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


inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << "key_callback: key=" << key << " scancode=" << scancode << " action=" << action << " mods=" << mods << std::endl;
	if (action != GLFW_PRESS && action != GLFW_REPEAT)
	{
		return;
	}
	switch (key)
	{
	case GLFW_KEY_UP:
		selected == -1 ? scene.rotate(5.0f, 0.0f) : chain[selected].rotate(5.0f, 0.0f);
		break;
	case GLFW_KEY_DOWN:
		selected == -1 ? scene.rotate(-5.0f, 0.0f) : chain[selected].rotate(5.0f, 0.0f);
		break;
	case GLFW_KEY_RIGHT:
		selected == -1 ? scene.rotate(0.0f, -5.0f) : chain[selected].rotate(0.0f, -5.0f);
		break;
	case GLFW_KEY_LEFT:
		selected == -1 ? scene.rotate(0.0f, 5.0f) : chain[selected].rotate(0.0f, 5.0f);
		break;
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	default:
		break;
	}
}

inline void translateToMouse(float xpos, float ypos)
{
	float xRel = prevX - xpos;
	float yRel = prevY - ypos;
	std::cout << xRel << "," << yRel << std::endl;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	auto relation = float(DISPLAY_WIDTH) / float(DISPLAY_HEIGHT);
	auto z = pFAR + *depth * (pNEAR - pFAR);
	auto transX = relation * xRel / float(viewport[2]) * pNEAR * 2.0 * glm::tan(CAM_ANGLE * PI / 360.0) * (pFAR / z);
	auto transY = yRel / float(viewport[3]) * pNEAR * 2.0 * glm::tan(CAM_ANGLE * PI / 360.0) * (pFAR / z);

	if (selected == ARRAY_LENGTH)
	{
		chain[ARRAY_LENGTH].translate(vec3(transX, 0.0f, -transY));
	}
	else if (selected >= 0)
	{
		chain[0].translate(vec3(transX, 0.0f, -transY / 2.0f));
	}
	prevX = xpos;
	prevY = ypos;
}

inline void rotateToMouse(float xpos, float ypos)
{
	float xRel = prevX - xpos;
	float yRel = prevY - ypos;

	selected == -1 ? scene.rotate(yRel, xRel) : chain[selected].rotate(yRel, xRel);

	prevX = xpos;
	prevY = ypos;
}

inline void drawScene(Shader& shader, bool drawAxis)
{
	display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
	shader.Bind();

	M = scene.rotates * chain[ARRAY_LENGTH].translates * chain[ARRAY_LENGTH].rotates;
	M = glm::rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f)) * M;
	MVP = P * M;
	shader.Update(MVP, M, chain[ARRAY_LENGTH].color);
	mesh.Draw();

	for (auto i = 0; i < ARRAY_LENGTH; i++)
	{
		if (i == 0)
		{
			M = scene.rotates * chain[i].rotates * chain[i].translates;
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

	for (auto i = 0; i < ARRAY_LENGTH + 1 && !selection; i++)
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
	//std::cout << "mouse_callback: button=" << button << ", action=" << action << ", mods=" << mods << std::endl;

	glfwGetCursorPos(window, &prevX, &prevY);
	prevY = DISPLAY_HEIGHT - prevY;
	glReadPixels(prevX, prevY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, depth);
	std::cout << "Cursor Position at (" << prevX << " : " << prevY << "), depth = " << depth << std::endl;

	if(action == GLFW_PRESS)
	{
		drawScene(colorpickShader, false);
		pick(prevX, prevY);
	}

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		switch (action)
		{
		case GLFW_PRESS:
			rotateMouse = true;
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
	auto dst = vec3(0.0f, yOffset, 0.0f);
	if (selected == ARRAY_LENGTH)
	{
		chain[ARRAY_LENGTH].translate(dst);
	}
	else if (selected >= 0)
	{
		chain[0].translate(dst);
	}
}

inline void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
	//std::cout << "cursor_position_callback: xpos=" << xpos << ", ypos=" << ypos << std::endl;
	ypos = DISPLAY_HEIGHT - ypos;
	if (translateMouse)
	{
		translateToMouse(xpos, ypos);
	}
	if (rotateMouse)
	{
		rotateToMouse(xpos, ypos);
	}
}