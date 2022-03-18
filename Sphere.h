#pragma once
#include "Shape.h"


class Sphere :
	public Shape
{
public:
	Sphere(glm::vec3 position, float radius, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s);
	~Sphere();
	float getIntersection(ray lray, float t0, float t1);
	glm::vec3 getNormal(glm::vec3 inter);

private:
	glm::vec3 position;
	float radius;
};
