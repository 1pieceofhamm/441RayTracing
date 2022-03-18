#pragma once
#include "Shape.h"


class Plane :
	public Shape
{
public:
	Plane(glm::vec3 center, glm::vec3 normal, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s);
	~Plane();
	float getIntersection(ray lray, float t0, float t1);
	glm::vec3 getNormal(glm::vec3 inter);
private:
	glm::vec3 center, normal;
};
