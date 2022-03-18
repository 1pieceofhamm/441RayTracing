#pragma once
#include <vector>
#include "Shape.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"



class Scene
{
public:
	Scene(std::vector<Shape*> shapes, std::vector<Light*> lights);
	~Scene();
	bool Hit(ray hray, float t0, float t1, rec* hrec);
	void setCount(int set);
	glm::vec3 ComputeRayColor(ray lray, float t0, float t1);

private:
	int counter;
	std::vector<Shape*> shapes;
	std::vector<Light*> lights;

};
