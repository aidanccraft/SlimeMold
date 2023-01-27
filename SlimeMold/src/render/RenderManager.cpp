#include "Global.h"

#include "RenderManager.h"

RenderManager::RenderManager(WindowManager* win_mgr) {
	this->win_mgr = win_mgr;

	renderShader = new RenderShader("render");
	slimeShader = new SlimeShader("slime");
	diffuseShader = new DiffuseShader("diffuse");

	gui = new Gui();

	loadModel(quad);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
}

RenderManager::~RenderManager() {
	delete renderShader;
	delete slimeShader;
	delete diffuseShader;
	delete gui;
}

void RenderManager::loadModel(const float* quad) {
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), quad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderManager::render(unsigned int diffuseTex) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTex);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int RenderManager::initializeTexture(int width, int height) {
	unsigned int texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

void RenderManager::runSlimeCompute(unsigned int diffuseTexOld, unsigned int intermediateTex,
	int x, int y, int z) {
	glActiveTexture(GL_TEXTURE1);
	glActiveTexture(GL_TEXTURE2);

	glClearTexImage(intermediateTex, 0, GL_RGBA, GL_FLOAT, NULL);

	glBindImageTexture(1, diffuseTexOld, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glBindImageTexture(2, intermediateTex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

	slimeShader->dispatch(x, y, z);
}

void RenderManager::runDiffuseCompute(unsigned int diffuseTexOld, unsigned int diffuseTexNew, unsigned int intermediateTex,
	int x, int y, int z) {
	glActiveTexture(GL_TEXTURE1);
	glActiveTexture(GL_TEXTURE2);
	glActiveTexture(GL_TEXTURE3);

	glBindImageTexture(1, diffuseTexOld, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glBindImageTexture(2, intermediateTex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);
	glBindImageTexture(3, diffuseTexNew, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

	diffuseShader->dispatch(x, y, z);
}