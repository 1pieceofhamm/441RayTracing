#include "Sphere.h"

#include <algorithm> 
#include <iostream>

Sphere::Sphere(glm::vec3 position, float radius, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s) : Shape(ka, kd, ks, km, s) //constructor
{
	this->position = position;
	this->radius = radius;
	/*this->ka = ka;
	this->kd = kd;
	this->ks = ks;
	this->km = km;
	this->s = s;*/
	

}

Sphere::~Sphere()
{
}
float Sphere::getIntersection(ray lray, float t0, float t1) {
	//std::cout << "Made it"<< std::endl;
	float t;
	float tp; //positive
	float tm; //negative 
	//quadratic formula with determinant
	float a = dot(lray.direction, lray.direction);
	//std::cout << a << std::endl;
	float b = dot((2.0f * (lray.origin - this->position)), lray.direction);
	float c = dot((lray.origin - this->position), (lray.origin - this->position)) - pow(this->radius, 2);
	float det = pow(b, 2) - (4*a*c); //determinant
	//std::cout << det << std::endl;
	if (det < 0) {//no intersection
		return -1;
	}
	else if (det > 0) { //intersection
		tp = ((-1 * b) + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a); //positive quad formula
		tm = ((-1 * b) - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a); //negative quad formula
		t = std::min(tp, tm); //get minimum
		if (t >= t0 && t < t1) {
			return t;
		}
		else {
			return -1;
		}
	}
	else { //det must equal zero
		t = (-1 * b) / (2 * a);
		if (t >= t0 && t < t1) {
			return t;
		}
		else {
			return -1;
		}

	}
}
glm::vec3 Sphere::getNormal(glm::vec3 inter) {
	return normalize(inter - this->position);
}
