#include "SlimeShader.h"

SlimeShader::SlimeShader(const std::string& key) : Shader(ShaderType::COMPUTE, key) {
	getAllUniformLocations();
}

void SlimeShader::getAllUniformLocations() {
	location_sensorAngle = glGetUniformLocation(programID, "sensorAngle");
	location_sensorDistance = glGetUniformLocation(programID, "sensorDistance");
	location_turnSensitivity = glGetUniformLocation(programID, "turnSensitivity");
	location_movementSpeed = glGetUniformLocation(programID, "movementSpeed");
}

void SlimeShader::loadSensorAngle(float sensorAngle) {
	loadFloat(location_sensorAngle, sensorAngle);
}

void SlimeShader::loadSensorDistance(float sensorDistance) {
	loadFloat(location_sensorDistance, sensorDistance);
}

void SlimeShader::loadTurnSensitivity(float turnSensitivity) {
	loadFloat(location_turnSensitivity, turnSensitivity);
}

void SlimeShader::loadMovementSpeed(float movementSpeed) {
	loadFloat(location_movementSpeed, movementSpeed);
}