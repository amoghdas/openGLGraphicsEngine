#include "light.h"

Light::Light() {
	colour_ = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity_ = 1.0f;

	direction_ = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuseIntensity_ = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat dIntensity) {
	colour_ = glm::vec3(red, green, blue);
	ambientIntensity_ = aIntensity;

	direction_ = glm::vec3(xDir, yDir, zDir);
	diffuseIntensity_ = dIntensity;
}

void Light::useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation) {
	glUniform3f(ambientColourLocation, colour_.x, colour_.y, colour_.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity_);

	glUniform3f(directionLocation, direction_.x, direction_.y, direction_.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity_);
}

Light::~Light() {

}