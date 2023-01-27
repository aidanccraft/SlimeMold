#pragma once

#include "Global.h"
#include "render/Shader.h"

class DiffuseShader : public Shader {
private:
	unsigned int location_diffuseRate = 0;
	unsigned int location_decayRate = 0;
public:
	DiffuseShader(const std::string& key);
	void getAllUniformLocations() override;
	void loadDiffuseRate(float diffuseRate);
	void loadDecayRate(float decayRate);
};