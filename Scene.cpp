#include "Scene.h"
#include "rec.h"
#include "ray.h"
#include <algorithm>
#include <iostream>

Scene::~Scene()
{
	
}

Scene::Scene(std::vector<Shape*> shapes, std::vector<Light*> lights)
{
	this->shapes = shapes;
	this->lights = lights;

}
bool Scene::Hit(ray hray, float t0, float t1, rec* hrec) {
	float temp = t1;
	for (int i = 0; i < shapes.size(); i++) {
		//std::cout << shapes.at(i)->getKa().x << std::endl;
		float currentT = shapes.at(i)->getIntersection(hray, t0, t1);
		//std::cout << currentT << std::endl;
		if (currentT < temp && currentT >= 0) {
			temp = currentT;

			hrec->ka = shapes.at(i)->getKa(); //set the values of ka,kd,km,ks,s to the rec
			hrec->kd = shapes.at(i)->getKd();
			hrec->km = shapes.at(i)->getKm();
			hrec->ks = shapes.at(i)->getKs();
			hrec->s = shapes.at(i)->getS();
			
			glm::vec3 intersectPt = hray.origin + (temp * normalize(hray.direction)); //find intersection point
			hrec->point = intersectPt;
			hrec->normal = normalize(shapes.at(i)->getNormal(intersectPt));
		}
	}
	if (temp == t1) { 
		return false; //no hit
	}
	return true; //hit
}
void Scene::setCount(int set) { //counter for recursion
	counter = set;
}
glm::vec3 Scene::ComputeRayColor(ray lray, float t0, float t1) {
	counter++; //increment counter for recursion
	rec sRec; //scene Rec
	ray shadowRay;
	rec shadowRec;
	ray rray; //reflection ray
	if (this->Hit(lray, 0, INFINITY, &sRec)) { //call hit function
		
		glm::vec3 c = sRec.ka;
		shadowRay.origin = sRec.point;
		for (int i = 0; i < lights.size(); i++) {
			shadowRay.direction = normalize(lights.at(i)->getPosition() - shadowRay.origin);
			float tlight = dot((lights.at(i)->getPosition() - shadowRay.origin), shadowRay.direction) / dot(shadowRay.direction, shadowRay.direction);
			
			if ((!this->Hit(shadowRay, 0.001, tlight, &shadowRec))) {
				glm::vec3 lightVector = normalize(lights.at(i)->getPosition() - sRec.point); //calculations of vectors for reflection and light
				glm::vec3 eyeVector = normalize(lray.origin - sRec.point);
				glm::vec3 reflectVector = normalize(((2 * dot(lightVector, sRec.normal)) * sRec.normal) - lightVector);
				glm::vec3 specular = sRec.ks * pow(std::max(0.0f, dot(reflectVector, eyeVector)), sRec.s);
				glm::vec3 diffuse = sRec.kd * std::max(0.0f, dot(lightVector, sRec.normal));
				c += lights.at(i)->getColor() * (diffuse + specular);
			}
		}
		if (counter <= 4) { //go back in for recursion
			
			if (sRec.km.x > 0 || sRec.km.y > 0 || sRec.km.z > 0) { //reflection recursion
				rray.origin = sRec.point;
				rray.direction = normalize(((2 * dot(lray.direction, sRec.normal)) * sRec.normal) - lray.direction);
				rray.direction.x = rray.direction.x * -1; //setting reflection direction since its opposite
				rray.direction.y = rray.direction.y * -1;
				rray.direction.z = rray.direction.z * -1;
				c += sRec.km * ComputeRayColor(rray, 0.001, INFINITY);
			}
		}
		return c;
	}
	else {
		//std::cout << "no hit" << std::endl;
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
}
