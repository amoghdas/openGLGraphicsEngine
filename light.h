#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity);

	void useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
		GLfloat diffuseIntesityLocation, GLfloat directionLocation);


	~Light();

private:
	glm::vec3 colour_;
	GLfloat ambientIntensity_;

	glm::vec3 direction_;
	GLfloat diffuseIntensity_;
};

