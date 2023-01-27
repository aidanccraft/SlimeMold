#pragma once

#include <string>

#include "Global.h"

class WindowManager {
private:
    GLFWwindow* window;
    GLFWmonitor* monitor;
    const GLFWvidmode* mode;

    int window_width;
    int window_height;
    const std::string TITLE = "Slime Mold Simulation";
    const double VERSION = 1.0;

    bool fullscreen = false;
    int startup_width;
    double content_scale;

    bool keys[GLFW_KEY_LAST];
    bool buttons[3];

    void updateInput();
    void updateWindowFunctions();
public:
    WindowManager();
    ~WindowManager();

    bool isKeyDown(int key);
    bool isKeyPressed(int key);
    bool isKeyReleased(int key);

    bool isMouseButtonDown(int button);
    bool isMouseButtonPressed(int button);
    bool isMouseButtonReleased(int button);

    glm::vec2 getMousePosition();

    void updateWindow();

    void createWindow();
    GLFWwindow* getWindow();

    int getWindowWidth();
    int getWindowHeight();
    float getContentScale();
};