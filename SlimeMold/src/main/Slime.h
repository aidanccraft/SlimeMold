#pragma once

#include "Global.h"

struct SlimeCell {
	glm::vec2 position;
	float orientation;
	int type;
};

class Slime {
public:
	SlimeCell* slimeData;
	int units;
	unsigned int bufferID;

	unsigned int diffuseTexOld, diffuseTexNew, intermediateTex;

	Slime(int units, int width, int height);
	~Slime();

	unsigned int createBuffer();
	void flipTextures();
	void loadTextures(unsigned int diffuseTexOld, unsigned int diffuseTexNew, unsigned int intermediateTex);
};

