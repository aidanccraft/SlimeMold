#pragma once

#include "Global.h"
#include "render/Shader.h"

class RenderShader : public Shader {
private:
	unsigned int location_baseColor;
	unsigned int location_midColor;
	unsigned int location_fullColor;
public:
	RenderShader(const std::string& key);
	void getAllUniformLocations() override;
	void loadBaseColor(glm::vec3 baseColor);
	void loadMidColor(glm::vec3 midColor);
	void loadFullColor(glm::vec3 fullColor);
};