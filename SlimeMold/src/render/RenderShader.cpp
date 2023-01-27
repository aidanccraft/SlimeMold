#include "RenderShader.h"

RenderShader::RenderShader(const std::string& key) : Shader(ShaderType::VERTFRAG, key) {
	getAllUniformLocations();
}

void RenderShader::getAllUniformLocations() {
	location_baseColor = glGetUniformLocation(programID, "baseColor");
	location_midColor = glGetUniformLocation(programID, "midColor");
	location_fullColor = glGetUniformLocation(programID, "fullColor");
}

void RenderShader::loadBaseColor(glm::vec3 baseColor) {
	loadVec4f(location_baseColor, glm::vec4(baseColor, 1.0));
}

void RenderShader::loadMidColor(glm::vec3 midColor) {
	loadVec4f(location_midColor, glm::vec4(midColor, 1.0));
}

void RenderShader::loadFullColor(glm::vec3 fullColor) {
	loadVec4f(location_fullColor, glm::vec4(fullColor, 1.0));
}