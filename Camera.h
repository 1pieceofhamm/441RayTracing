#pragma once
#include <vector>
#include "Scene.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


class Camera
{
public:
	Camera();
	~Camera();

	Camera(int widthRes, int heightRes, glm::vec3 eye, glm::vec3 lookat, glm::vec3 up, int fovy, float focaldist);

	void TakePicture(Scene *scene);
	float* GetRenderedImage() { return renderedImage; };

private:

	int widthRes;
	int heightRes;
	glm::vec3 eye; 
	glm::vec3 lookat;
	glm::vec3 up; 
	int fovy; 
	float focaldist;
	float *renderedImage;


};
