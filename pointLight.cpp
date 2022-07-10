#include "pointLight.h"

PointLight::PointLight() : Light() {
    position_ = glm::vec3(0.0f, 0.0f, 0.0f);
    constant_ = 1.0f;
    linear_ = 0.0f;
    exponent_ = 0.0f;
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
    GLfloat aIntensity, GLfloat dIntensity,
    GLfloat xPos, GLfloat yPos, GLfloat zPos,
    GLfloat con, GLfloat lin, GLfloat exp) : Light(red, green, blue, aIntensity, dIntensity) {
    position_ = glm::vec3(xPos, yPos, zPos);
    constant_ = con;
    linear_ = lin;
    exponent_ = exp;
}

void PointLight::useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
                          GLfloat diffuseIntensityLocation, GLfloat positionLocation,
                          GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation) {
    glUniform3f(ambientColourLocation, colour_.x, colour_.y, colour_.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity_);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity_);

    glUniform3f(positionLocation, position_.x, position_.y, position_.z);
    glUniform1f(constantLocation, constant_);
    glUniform1f(linearLocation, linear_);
    glUniform1f(exponentLocation, exponent_);
}

PointLight::~PointLight() {

}


