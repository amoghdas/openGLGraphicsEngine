#include "shader.h"

Shader::Shader() {
	shaderID_ = 0;
	uniformModel_ = 0;
	uniformProjection_ = 0;

	pointLightCount_ = 0;
}

void Shader::createFromString(const char *vertexCode, const char *fragmentCode) {
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation) {
	std::string vertexString = readFile(vertexLocation);
	std::string fragmentString = readFile(fragmentLocation);

	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char *fileLocation) {
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "Failed to read " << fileLocation << "! File doesn't exist.\n";
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::compileShader(const char *vertexCode, const char *fragmentCode) {
	shaderID_ = glCreateProgram();

	if (!shaderID_) {
		std::cout << "Error creating shader program!\n";
		return;
	}

	addShader(shaderID_, vertexCode, GL_VERTEX_SHADER);
	addShader(shaderID_, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID_);
	glGetProgramiv(shaderID_, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID_, sizeof(eLog), NULL, eLog);
		std::cout << "Error linking program: '" << eLog << "'\n";
		return;
	}

	glValidateProgram(shaderID_);
	glGetProgramiv(shaderID_, GL_VALIDATE_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID_, sizeof(eLog), NULL, eLog);
		std::cout << "Error validating program: '" << eLog << "'\n";
		return;
	}

	uniformProjection_ = glGetUniformLocation(shaderID_, "projection");
	uniformModel_ = glGetUniformLocation(shaderID_, "model");
	uniformView_ = glGetUniformLocation(shaderID_, "view");
	uniformDirectionalLight_.uniformColour_ = glGetUniformLocation(shaderID_, "directionalLight.base.colour");
	uniformDirectionalLight_.uniformAmbientIntensity_ = glGetUniformLocation(shaderID_, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight_.uniformDirection_ = glGetUniformLocation(shaderID_, "directionalLight.direction");
	uniformDirectionalLight_.uniformDiffuseIntensity_ = glGetUniformLocation(shaderID_, "directionalLight.base.diffuseIntensity");
	uniformSpecularIntensity_ = glGetUniformLocation(shaderID_, "material.specularIntensity");
	uniformShininess_ = glGetUniformLocation(shaderID_, "material.shininess");
	uniformEyePosition_ = glGetUniformLocation(shaderID_, "eyePosition");

	uniformPointLightCount_ = glGetUniformLocation(shaderID_, "pointLightCount");

	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++) {
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour", i);
		uniformPointLight_[i].uniformColour_ = glGetUniformLocation(shaderID_, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLight_[i].uniformAmbientIntensity_ = glGetUniformLocation(shaderID_, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLight_[i].uniformDiffuseIntensity_ = glGetUniformLocation(shaderID_, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
		uniformPointLight_[i].uniformPosition_ = glGetUniformLocation(shaderID_, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.constant", i);
		uniformPointLight_[i].uniformConstant_ = glGetUniformLocation(shaderID_, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.linear", i);
		uniformPointLight_[i].uniformLinear_ = glGetUniformLocation(shaderID_, locBuff);

		snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.exponent", i);
		uniformPointLight_[i].uniformExponent_ = glGetUniformLocation(shaderID_, locBuff);
	}
}

GLuint Shader::getProjectionLocation() {
	return uniformProjection_;
}

GLuint Shader::getModelLocation() {
	return uniformModel_;
}

GLuint Shader::getViewLocation() {
	return uniformView_;
}

GLuint Shader::getAmbientIntensityLocation() {
	return uniformDirectionalLight_.uniformAmbientIntensity_;
}

GLuint Shader::getAmbientColourLocation() {
	return uniformDirectionalLight_.uniformColour_;
}

GLuint Shader::getDiffuseIntensityLocation() {
	return uniformDirectionalLight_.uniformDiffuseIntensity_;
}

GLuint Shader::getDirectionLocation() {
	return uniformDirectionalLight_.uniformDirection_;
}

GLuint Shader::getSpecularIntensityLocation() {
	return uniformSpecularIntensity_;
}

GLuint Shader::getShininessLocation() {
	return uniformShininess_;
}

GLuint Shader::getEyePositionLocation() {
	return uniformEyePosition_;
}

void Shader::setDirectionalLight(DirectionalLight* dLight) {
	dLight->useLight(uniformDirectionalLight_.uniformAmbientIntensity_, uniformDirectionalLight_.uniformColour_,
		uniformDirectionalLight_.uniformDiffuseIntensity_, uniformDirectionalLight_.uniformDirection_);
}

void Shader::setPointLights(PointLight* pLight, unsigned int lightCount) {
	if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

	glUniform1i(uniformPointLightCount_, lightCount);

	for (size_t i = 0; i < lightCount; i++) {
		pLight[i].useLight(uniformPointLight_[i].uniformAmbientIntensity_,
							uniformPointLight_[i].uniformColour_,
							uniformPointLight_[i].uniformDiffuseIntensity_,
							uniformPointLight_[i].uniformPosition_,
							uniformPointLight_[i].uniformConstant_,
							uniformPointLight_[i].uniformLinear_,
							uniformPointLight_[i].uniformExponent_);
	}
}

void Shader::useShader() {
	glUseProgram(shaderID_);
}

void Shader::clearShader() {
	if (shaderID_ != 0) {
		glDeleteProgram(shaderID_);
		shaderID_ = 0;
	}

	uniformModel_ = 0;
	uniformProjection_ = 0;
}


void Shader::addShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		std::cout << "Error compiling the " << shaderType << " shader: '" << eLog << "'\n";
		return;
	}

	glAttachShader(theProgram, theShader);
}

Shader::~Shader() {
	clearShader();
}






