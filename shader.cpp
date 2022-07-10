#include "shader.h"

Shader::Shader() {
	shaderID_ = 0;
	uniformModel_ = 0;
	uniformProjection_ = 0;
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

	uniformModel_ = glGetUniformLocation(shaderID_, "model");
	uniformProjection_ = glGetUniformLocation(shaderID_, "projection");
	uniformView_ = glGetUniformLocation(shaderID_, "view");
	uniformDirectionalLight_.uniformColour_ = glGetUniformLocation(shaderID_, "directionalLight.colour");
	uniformDirectionalLight_.uniformAmbientIntensity_ = glGetUniformLocation(shaderID_, "directionalLight.ambientIntensity");
	uniformDirectionalLight_.uniformDirection_ = glGetUniformLocation(shaderID_, "directionalLight.direction");
	uniformDirectionalLight_.uniformDiffuseIntensity_ = glGetUniformLocation(shaderID_, "directionalLight.diffuseIntensity");
	uniformSpecularIntensity_ = glGetUniformLocation(shaderID_, "material.specularIntensity");
	uniformShininess_ = glGetUniformLocation(shaderID_, "material.shininess");
	uniformEyePosition_ = glGetUniformLocation(shaderID_, "eyePosition");
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






