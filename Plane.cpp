#include "Plane.h"
#include <iostream>

Plane::Plane(glm::vec3 center, glm::vec3 normal, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s) : Shape (ka,kd,ks,km,s) //constructor
{
	this->center = center;
	this->normal = normal;
	/*this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->km = km;
	this->s = s;*/
}

Plane::~Plane()
{
}
float Plane::getIntersection(ray lray, float t0, float t1) {
	float t = dot((this->center - lray.origin), this->normal) / dot(lray.direction, this->normal);
	//std::cout << t << std::endl;
	if (t >= t0 && t < t1) {
		return t;
	}
	return -1;
}
glm::vec3 Plane::getNormal(glm::vec3 inter) {
	return this->normal;
}
