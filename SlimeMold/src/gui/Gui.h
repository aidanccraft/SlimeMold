#pragma once

#include "Global.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class Gui {
public:
    float sensorAngle = 3.1415926535898f / 3;
    float sensorDistance = 8.0f;
    float turnSensitivity = 3.1415926535898f / 4;
    float movementSpeed = 1.35f;

    float diffuseRate = 0.7f;
    float decayRate = 0.05f;

    float baseColor[3] = { 0.0f, 0.0f, 0.0f };
    float midColor[3] = { 23 / 255.0f, 63 / 255.0f, 95 / 255.0f };
    float fullColor[3] = { 60 / 255.0f, 174 / 255.0f, 163 / 255.0f };

	void initGUI(GLFWwindow* window);
	void render();
	void renderGUI();
	void cleanup();
};

