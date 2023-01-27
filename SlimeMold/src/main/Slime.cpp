#include "Slime.h"

#include <stdlib.h>
#include <time.h>


Slime::Slime(int units, int width, int height) {
	slimeData = new SlimeCell[units];

	this->units = units;

	srand(time(NULL));

	for (int i = 0; i < units; i++) {
		slimeData[i].orientation = (float)rand() / RAND_MAX * (2 * 3.14159265358);
		slimeData[i].position = glm::vec2(rand() % (width), rand() % (height));

		//slimeData[i].orientation = (float)rand() / RAND_MAX * (2 * 3.14159265358);
		//slimeData[i].position = glm::vec2(width / 2 + (rand() % 200) * sin(slimeData[i].orientation), height / 2 - (rand() % 200) * cos(slimeData[i].orientation));

		slimeData[i].type = 1;
	}

	bufferID = createBuffer();
}

Slime::~Slime() {
	delete[] slimeData;
}

unsigned int Slime::createBuffer() {
	unsigned int ssbo;

	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, units * sizeof(SlimeCell), slimeData, GL_DYNAMIC_COPY);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	return ssbo;
}

void Slime::flipTextures() {
	unsigned int tempTex = diffuseTexNew;
	diffuseTexNew = diffuseTexOld;
	diffuseTexOld = tempTex;
}

void Slime::loadTextures(unsigned int diffuseTexOld, unsigned int diffuseTexNew, unsigned int intermediateTex) {
	this->diffuseTexOld = diffuseTexOld;
	this->diffuseTexNew = diffuseTexNew;
	this->intermediateTex = intermediateTex;
}