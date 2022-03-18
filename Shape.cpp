#include "Shape.h"


Shape::Shape(void)
{
}

Shape::Shape(glm::vec3 ka1, glm::vec3 kd1, glm::vec3 ks1, glm::vec3 km1, float s1) : ka(ka1), kd(kd1), ks(ks1), km(km1), s(s1) //constructor
{

}

Shape::~Shape(void)
{
}
float Shape::getIntersection(ray lray, float t0, float t1) {
	return 0;
}
glm::vec3 Shape::getNormal(glm::vec3 inter) {
	return glm::vec3(0.0,0.0,0.0);
}
glm::vec3 Shape::getKa() { //getters
	return ka;
}
glm::vec3 Shape::getKd() {
	return kd;
}
glm::vec3 Shape::getKs() {
	return ks;
}
glm::vec3 Shape::getKm() {
	return km;
}
float Shape::getS() {
	return s;
}