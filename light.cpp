#include "light.h"

Light::Light() {
	colour_ = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity_ = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity) {
	colour_ = glm::vec3(red, green, blue);
	ambientIntensity_ = aIntensity;
}

void Light::useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation) {
	glUniform3f(ambientColourLocation, colour_.x, colour_.y, colour_.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity_);
}

Light::~Light() {

}