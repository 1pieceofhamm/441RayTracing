#include "Light.h"


Light::Light(glm::vec3 position, glm::vec3 color) //constructor
{
	this->position = position;
	this->color = color;
}

Light::~Light(void)
{
}
glm::vec3 Light::getPosition() { //getters
	return position;
}
glm::vec3 Light::getColor() {
	return color;
}