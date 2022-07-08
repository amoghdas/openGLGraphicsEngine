#include "directionalLight.h"

DirectionalLight::DirectionalLight() : Light() {
	direction_ = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir) : Light(red, green, blue, aIntensity, dIntensity) {
	direction_ = glm::vec3(xDir, yDir, zDir);
}

void DirectionalLight::useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
	GLfloat diffuseIntensityLocation, GLfloat directionLocation) {
	glUniform3f(ambientColourLocation, colour_.x, colour_.y, colour_.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity_);

	glUniform3f(directionLocation, direction_.x, direction_.y, direction_.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity_);
}

DirectionalLight::~DirectionalLight() {

}