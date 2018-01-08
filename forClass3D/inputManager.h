#pragma once
#include "GLFW/glfw3.h"
#include "Cube.h"
#include "Scene.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

static const int ARRAY_LENGTH = 4;
static const float AXIS_LENGTH = 10.0f;
static const float ROTATION_LIMIT = 45.0f;

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 800;
static const float CAM_ANGLE = 60.0f;
static const float pNEAR = 0.1f;
static const float pFAR = 100.0f;
static const int CUBE_SIZE = 2;
static const glm::vec3 SCALE_FACTOR = glm::vec3(1.0f, 1.0f, 2.0f);
static const float PI = 3.14159265359f;
static const float maxDistance = ARRAY_LENGTH * CUBE_SIZE * 2;

Cube* chain;
Scene scene;
glm::mat4 M, N, P, MVP;

bool rotateMouse, translateMouse, ikSolver;
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

inline void printVector(std::string name, vec3 v)
{
	std::cout << name << "= (" << v.x << "," << v.y << "," << v.z << ")" << std::endl;
}

inline vec3 getCoords(mat4 M)
{
	return vec3(M[3][0], M[3][1], M[3][2]);
}

inline void printCube(int index)
{
	auto M = chain[index].M;
	vec3 position;
	if (index != ARRAY_LENGTH)
	{
		M = translate(M, vec3(0.0f, 0.0f, 1.0f));
	}
	position = getCoords(M);
	std::cout << "Cube[" << index << "]: " <<
		"pos(" << position.x << ", " << position.y << ", " << position.z << "); " <<
		"angles(" << chain[index].angles.x << ", " << chain[index].angles.y << ", " << chain[index].angles.z << ")" <<
		std::endl;
}

inline void drawLine(glm::vec3 p1, glm::vec3 p2)
{
	glLineWidth(1);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(p1.x, p1.y, p1.z);
	glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
}

inline void reset()
{
	for (auto i = 0; i < ARRAY_LENGTH + 1; i++)
	{
		chain[i].reset();
		chain[ARRAY_LENGTH].translate(vec3(5.0f, 0.0f, 0.0f));
		scene.reset();
		selected = -1;
	}
}

int current = ARRAY_LENGTH - 1;
inline void ccdStep()
{
	auto epsilon = 0.5;

	auto E = getCoords(glm::translate(chain[ARRAY_LENGTH - 1].M, vec3(0, 0, 1)));
	auto D = getCoords(chain[ARRAY_LENGTH].M);
	auto R = getCoords(glm::translate(chain[current].M, vec3(0, 0, -1)));
	printVector("R", R);
	printVector("E", E);
	printVector("D", D);

	if (distance(E, D) < epsilon)
	{
		ikSolver = false;
		return;
	}

	auto RE = normalize(E - R);
	auto RD = normalize(D - R);
	printVector("RE", RE);
	printVector("RD", RD);

	auto theta = degrees(acos(clamp(dot(RE, RD), -0.99f, 0.99f)));
	auto plane = cross(RE, RD);
	printVector("Plane", plane);

	theta = R.x < D.x ? theta : -theta;
	std::cout << "theta = " << theta << std::endl;
	chain[current].rotate(theta, vec3(0.0f, 1.0f, 0.0f));
	//chain[a].rotate(theta, vec3(plane.x, 0.0f, 0.0f));
	//chain[a].rotate(theta, vec3(0.0f, plane.y, 0.0f));
	//chain[a].rotate(theta, vec3(0.0f, 0.0f, plane.z));
	std::cout << "rotate chain[" << current << "]" << std::endl;
	if (current == 0)
	{
		current = ARRAY_LENGTH;
	}
	current--;
}

inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//std::cout << "key_callback: key=" << key << " scancode=" << scancode << " action=" << action << " mods=" << mods << std::endl;
	if ((ikSolver && key != GLFW_KEY_SPACE) || (action != GLFW_PRESS && action != GLFW_REPEAT))
	{
		return;
	}
	vec3 src, dst;
	switch (key)
	{
	case GLFW_KEY_SPACE:
		src = getCoords(glm::translate(chain[0].M, vec3(0, 0, -1)));
		dst = getCoords(chain[ARRAY_LENGTH].M);

		if(distance(src, dst) > maxDistance)
		{
			std::cout << "Error: can't reach!" << std::endl;
		} else
		{
			ikSolver = !ikSolver;
			if (!ikSolver)
			{
				reset();
			}
		}
		break;
	case GLFW_KEY_F: {
		ccdStep();
		break;
	}
	case GLFW_KEY_UP:
		selected == -1 ? scene.rotate(5.0f, 0.0f) : chain[selected].rotate(5.0f, 0.0f);
		printCube(selected);
		break;
	case GLFW_KEY_DOWN:
		selected == -1 ? scene.rotate(-5.0f, 0.0f) : chain[selected].rotate(-5.0f, 0.0f);
		printCube(selected);
		break;
	case GLFW_KEY_RIGHT:
		selected == -1 ? scene.rotate(0.0f, 5.0f) : chain[selected].rotate(0.0f, 5.0f);
		printCube(selected);
		break;
	case GLFW_KEY_LEFT:
		selected == -1 ? scene.rotate(0.0f, -5.0f) : chain[selected].rotate(0.0f, -5.0f);
		printCube(selected);
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
			selection = true;
			printCube(selected);
		}
	}
	if (!selection)
	{
		selected = -1;
		std::cout << "No selection performed." << std::endl;
	}
}

inline void drawScene(Shader& shader, bool drawAxis)
{
	display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
	shader.Bind();

	if (ikSolver)
	{
		ccdStep();
		//Sleep(2000);
	}

	M = chain[ARRAY_LENGTH].translates * scene.rotates * chain[ARRAY_LENGTH].rotates * chain[ARRAY_LENGTH].ikRotates;
	M = glm::rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f)) * M;
	chain[ARRAY_LENGTH].M = M;
	MVP = P * M;
	shader.Update(MVP, M, chain[ARRAY_LENGTH].color);
	mesh.Draw();

	for (auto i = 0; i < ARRAY_LENGTH; i++)
	{
		if (i == 0)
		{
			M = chain[i].translates * scene.rotates * chain[i].rotates * chain[i].ikRotates;
			M = glm::scale(SCALE_FACTOR) * M;
			M = glm::rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f)) * M;
		}
		else
		{
			M = N * glm::translate(vec3(0, 0, 1)) * chain[i].translates * chain[i].rotates * chain[i].ikRotates * glm::translate(vec3(0, 0, 1));
		}
		N = M;
		chain[i].M = M;
		MVP = P * M;
		shader.Update(MVP, M, chain[i].color);
		mesh.Draw();

		if (drawAxis)
		{
			drawLine(vec3(float(AXIS_LENGTH), 0.0f, -1.0f), vec3(-float(AXIS_LENGTH), 0.0f, -1.0f));
			drawLine(vec3(0.0f, 0.0f, float(AXIS_LENGTH)), vec3(0.0f, 0.0f, -float(AXIS_LENGTH)));
		}
	}
}

inline void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if(ikSolver)
	{
		return;
	}
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
	if (ikSolver)
	{
		return;
	}
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
	if (ikSolver)
	{
		return;
	}
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