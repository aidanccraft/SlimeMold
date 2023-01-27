#pragma once

#include "util/WindowManager.h"
#include "render/RenderManager.h"
#include "main/Slime.h"
#include "gui/Gui.h"

class Handler{
private:
    WindowManager* win_mgr;
    RenderManager* renderer;

    bool paused = false;
    int width, height;
    glm::vec2 slimeUnits;

    Slime* slime;

    void runSlimeShader();
    void runDiffuseShader();

public:
    Handler(WindowManager* win_mgr, RenderManager* renderer);
    ~Handler();
    void render();
    void tick();
};

