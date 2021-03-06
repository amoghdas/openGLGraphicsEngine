#pragma once
#include "light.h"

class DirectionalLight :
    public Light
{
public:
    DirectionalLight();
    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, 
                    GLfloat aIntensity, GLfloat dIntensity, 
                    GLfloat xDir, GLfloat yDir, GLfloat zDir);

    void useLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
        GLfloat diffuseIntesityLocation, GLfloat directionLocation);

    ~DirectionalLight();

private:
    glm::vec3 direction_;

};

