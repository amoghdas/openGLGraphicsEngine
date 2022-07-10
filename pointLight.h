#pragma once
#include "light.h"

class PointLight :
    public Light
{
public:
    PointLight();
    PointLight(GLfloat red, GLfloat green, GLfloat blue,
        GLfloat aIntensity, GLfloat dIntensity,
        GLfloat xPos, GLfloat yPos, GLfloat zPos,
        GLfloat con, GLfloat lin, GLfloat exp);

    void useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
        GLfloat diffuseIntensityLocation, GLfloat positionLocation,
        GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);

    ~PointLight();

private:
    glm::vec3 position_;
    GLfloat constant_, linear_, exponent_;
};

