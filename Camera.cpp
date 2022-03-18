#include "Camera.h"
#include <iostream>




Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera::Camera(int widthRes, int heightRes, glm::vec3 eye, glm::vec3 lookat, glm::vec3 up, int fovy, float focaldist) //constructor
{
	this->widthRes = widthRes;
	this->heightRes = heightRes;
	this->eye = eye;
	this->lookat = lookat;
	this->up = up;
	this->fovy = fovy;
	this->focaldist = focaldist;
	renderedImage = new float[widthRes * heightRes * 3];
}

void Camera::TakePicture(Scene *scene)
{
	memset(renderedImage, 0, sizeof(float) * widthRes * heightRes * 3);
	//creation of rays and vectors for the camera into coordinates
	ray sRay;
	glm::vec3 a = eye - lookat;
	glm::vec3 w = a / (length(a));
	glm::vec3 u = cross(up, w) / (length(cross(up, w)));
	glm::vec3 v = cross(w, u);
	glm::vec3 Ic = (eye + normalize(lookat - eye)) * focaldist;
	

	float ly = 2.0f * focaldist * tan(fovy / 2.0f);
	//float ly1 = 2.0f * focaldist * tan(fovy / 2.0f);
	//std::cout << ly << std::endl;
	float pw = ly / heightRes;
	float lx = pw * widthRes;
	
	glm::vec3 originPlane = Ic - ((lx / 2) * u) - ((ly / 2) * v); //Ic formula from notes
	
	for (int j = 0; j < heightRes; j++) { //loop for ray and color interpolation 
		for (int i = 0; i < widthRes; i++) { //for each pixel
			glm::vec3 Pc = originPlane + (float(i + 0.5) * (pw * u)) + (float(j + 0.5) * (pw * v));
			sRay.origin = eye;
			sRay.direction = normalize(Pc - eye);
			glm::vec3 sColor = scene->ComputeRayColor(sRay, 0, INFINITY);
			scene->setCount(0);
			renderedImage[(j * widthRes + i) * 3 + 0] = sColor[0]; //setting color of ray
			renderedImage[(j * widthRes + i) * 3 + 1] = sColor[1];
			renderedImage[(j * widthRes + i) * 3 + 2] = sColor[2];
		}
	}



	
}
