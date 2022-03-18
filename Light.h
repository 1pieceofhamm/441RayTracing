#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	~Light();
	glm::vec3 getPosition();
	glm::vec3 getColor();

private:
	glm::vec3 position;
	glm::vec3 color;

};
