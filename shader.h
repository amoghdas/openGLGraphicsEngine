#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <GL\glew.h>

#include "directionalLight.h"
#include "pointLight.h"

class Shader
{
public:
	Shader();

	void createFromString(const char *vertexCode, const char *fragmentCode);
	void createFromFiles(const char *vertexLocation, const char *fragmentLocation);

	std::string readFile(const char* fileLocation);

	GLuint getProjectionLocation();
	GLuint getModelLocation();
	GLuint getViewLocation();
	GLuint getAmbientIntensityLocation();
	GLuint getAmbientColourLocation();
	GLuint getDiffuseIntensityLocation();
	GLuint getDirectionLocation();
	GLuint getSpecularIntensityLocation();
	GLuint getShininessLocation();
	GLuint getEyePositionLocation();

	void setDirectionalLight(DirectionalLight *dLight);

	void useShader();
	void clearShader();

	~Shader();

private:
	int pointLightCount_;

	GLuint shaderID_, uniformProjection_, uniformModel_, uniformView_, uniformEyePosition_,
			uniformSpecularIntensity_, uniformShininess_;

	struct {
		GLuint uniformColour_;
		GLuint uniformAmbientIntensity_;
		GLuint uniformDiffuseIntensity_;

		GLuint uniformDirection_;
	} uniformDirectionalLight_;

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

