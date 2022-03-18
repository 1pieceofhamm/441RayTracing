#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "rec.h"
#include "ray.h"

class Shape
{
public:
	Shape(void);
	Shape(glm::vec3 ka1, glm::vec3 kd1, glm::vec3 ks1, glm::vec3 km1, float s1);

	~Shape(void);
	virtual float getIntersection(ray lray, float t0, float t1);
	virtual glm::vec3 getNormal(glm::vec3 inter);
	glm::vec3 getKa();
	glm::vec3 getKd();
	glm::vec3 getKs();
	glm::vec3 getKm();
	float getS();

private:
	glm::vec3 ka, kd, ks, km;
	float s;
	
};
