#pragma once

#include "Global.h"
#include "render/Shader.h"

class SlimeShader : public Shader {
private:
	unsigned int location_sensorAngle;
	unsigned int location_sensorDistance;
	unsigned int location_turnSensitivity;
	unsigned int location_movementSpeed;
public:
	SlimeShader(const std::string& key);
	void getAllUniformLocations() override;

	void loadSensorAngle(float sensorAngle);
	void loadSensorDistance(float sensorDistance);
	void loadTurnSensitivity(float turnSensitivity);
	void loadMovementSpeed(float movementSpeed);
};