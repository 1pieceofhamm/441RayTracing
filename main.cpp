#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Camera.h"
#include "Scene.h"
#include "Sphere.h"
#include "Plane.h"



#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1200

float frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];
GLFWwindow *window;

std::vector<Shape*> shapes;
std::vector<Light*> lights;



void ClearFrameBuffer()
{
	memset(&frameBuffer, 0, WINDOW_HEIGHT * WINDOW_WIDTH * 3 * sizeof(float));
}

void Display()
{	
	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_FLOAT, frameBuffer);
}

void Init()
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment5 - Caleb Hammack", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	ClearFrameBuffer();

	Sphere* sphere1 = new Sphere(glm::vec3(-1.0f, -0.7f, 3.0f), 0.3f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.2f, 1.0f, 0.2f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 100.0f);
	Sphere* sphere2 = new Sphere(glm::vec3(1.0f, -0.5f, 3.0f), 0.5f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), 10.0f);
	Sphere* sphere3 = new Sphere(glm::vec3(-1.0f, 0.0f, 0.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f);
	Sphere* sphere4 = new Sphere(glm::vec3(1.0f, 0.0f, -1.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.8f, 0.8f, 0.8f), 0.0f);

	Plane* plane1 = new Plane(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);
	Plane* plane2 = new Plane(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), 0.0f);

	Light* light1 = new Light(glm::vec3(0.0f, 3.0f, -2.0f), glm::vec3(0.2f, 0.2f, 0.2f));
	Light* light2 = new Light(glm::vec3(-2.0f, 1.0f, 4.0f), glm::vec3(0.5f, 0.5f, 0.5f));

	shapes.push_back(sphere1);
	shapes.push_back(sphere2);
    shapes.push_back(sphere3);
	shapes.push_back(sphere4);
	shapes.push_back(plane1);

	shapes.push_back(plane2);
	lights.push_back(light1);
	lights.push_back(light2);

	Scene scene = Scene(shapes,lights);
	Camera camera = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 1.0f);
	camera.TakePicture(&scene);
	float *renderedImage = camera.GetRenderedImage();
	memcpy(frameBuffer, renderedImage, sizeof(float) * WINDOW_HEIGHT * WINDOW_WIDTH * 3);
}


int main()
{	
	Init();
	while ( glfwWindowShouldClose(window) == 0) 
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Display();
		glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}