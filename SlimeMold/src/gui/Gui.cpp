#include "Gui.h"

void Gui::initGUI(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
}

void Gui::render() {
    ImGui::SetNextWindowSize(ImVec2(400, 340));
    ImGui::Begin("Slime Mold Simulation Settings", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    char slimeSettings[] = "Slime Agent Settings";
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth = ImGui::CalcTextSize(slimeSettings).x;
    ImGui::SetCursorPosX(70);

    ImGui::Text(slimeSettings);

    ImGui::SliderFloat("Sensor Angle", &sensorAngle, 0.0f, 2 * 3.1415926535898f);
    ImGui::SliderFloat("Sensor Distance", &sensorDistance, 0.0f, 50.0f);
    ImGui::SliderFloat("Turn Sensitivity", &turnSensitivity, 0.0f, 2 * 3.1415926535898f);
    ImGui::SliderFloat("Movement Speed", &movementSpeed, 0.0f, 50.0f);

    ImGui::Dummy(ImVec2(0.0f, 20.0f));
    ImGui::SetCursorPosX(78);

    ImGui::Text("Diffusion Settings");

    ImGui::SliderFloat("Diffuse Rate", &diffuseRate, 0.0f, 1.0f);
    ImGui::SliderFloat("Decay Rate", &decayRate, 0.0f, 0.1f);

    ImGui::Dummy(ImVec2(0.0f, 20.0f));
    ImGui::SetCursorPosX(86);
    ImGui::Text("Display Settings");

    ImGui::ColorEdit3("Base Color", baseColor);
    ImGui::ColorEdit3("Middle Color", midColor);
    ImGui::ColorEdit3("Full Color", fullColor);

    ImGui::End();
}

void Gui::renderGUI() {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::ShowDemoWindow();
    render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update viewports
    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);
}

void Gui::cleanup() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}