#include "DiffuseShader.h"

DiffuseShader::DiffuseShader(const std::string& key) : Shader(ShaderType::COMPUTE, key) {
	getAllUniformLocations();
}

void DiffuseShader::getAllUniformLocations() {
	location_diffuseRate = glGetUniformLocation(programID, "diffuseRate");
	location_decayRate = glGetUniformLocation(programID, "decayRate");
}


void DiffuseShader::loadDiffuseRate(float diffuseRate) {
	loadFloat(location_diffuseRate, diffuseRate);
}

void DiffuseShader::loadDecayRate(float decayRate) {
	loadFloat(location_decayRate, decayRate);
}