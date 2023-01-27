#pragma once

#include "Global.h"
#include "util/WindowManager.h"
#include "render/SlimeShader.h"
#include "render/DiffuseShader.h"
#include "render/RenderShader.h"
#include "gui/Gui.h"

class RenderManager {
private:
	WindowManager* win_mgr;

	float quad[8] = { -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f };

	void loadModel(const float* quad);

public:
	RenderShader* renderShader;
	SlimeShader* slimeShader;
	DiffuseShader* diffuseShader;

	Gui* gui;

	RenderManager(WindowManager* win_mgr);
	~RenderManager();
	void render(unsigned int diffuseTex);

	unsigned int initializeTexture(int width, int height);

	void runSlimeCompute(unsigned int diffuseTexOld, unsigned int intermediateTex,
		int x, int y, int z);
	void runDiffuseCompute(unsigned int diffuseTexOld, unsigned int intermediateTex, unsigned int diffuseTexNew,
		int x, int y, int z);
};