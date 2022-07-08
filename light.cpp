#include "light.h"

Light::Light() {
	colour_ = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity_ = 1.0f;
	diffuseIntensity_ = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, 
	GLfloat aIntensity, GLfloat dIntensity) {
	colour_ = glm::vec3(red, green, blue);
	ambientIntensity_ = aIntensity;
	diffuseIntensity_ = dIntensity;
}

Light::~Light() {

}