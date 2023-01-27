#include "Handler.h"

Handler::Handler(WindowManager* win_mgr, RenderManager* renderer) : win_mgr(win_mgr), renderer(renderer) {
    width = win_mgr->getWindowWidth();
    height = win_mgr->getWindowHeight();

    slimeUnits = glm::vec2(2000, 1000);

    slime = new Slime(slimeUnits.x * slimeUnits.y, width, height);
    slime->loadTextures(renderer->initializeTexture(width, height),
        renderer->initializeTexture(width, height),
        renderer->initializeTexture(width, height));

    tick();
    paused = true;
}

Handler::~Handler() {
    delete slime;
}

void Handler::render() {
    renderer->renderShader->start();

    renderer->renderShader->loadBaseColor(glm::vec3(renderer->gui->baseColor[0], renderer->gui->baseColor[1], renderer->gui->baseColor[2]));
    renderer->renderShader->loadMidColor(glm::vec3(renderer->gui->midColor[0], renderer->gui->midColor[1], renderer->gui->midColor[2]));
    renderer->renderShader->loadFullColor(glm::vec3(renderer->gui->fullColor[0], renderer->gui->fullColor[1], renderer->gui->fullColor[2]));

    renderer->render(slime->diffuseTexOld);

    renderer->renderShader->stop();
}

void Handler::tick() {
    if (win_mgr->isKeyPressed(GLFW_KEY_SPACE)) {
        paused = !paused;
    }

    if (!paused) {
        runSlimeShader();
        runDiffuseShader();
        slime->flipTextures();
    }
}

void Handler::runSlimeShader() {
    renderer->slimeShader->start();

    renderer->slimeShader->loadSensorAngle(renderer->gui->sensorAngle);
    renderer->slimeShader->loadSensorDistance(renderer->gui->sensorDistance);
    renderer->slimeShader->loadTurnSensitivity(renderer->gui->turnSensitivity);
    renderer->slimeShader->loadMovementSpeed(renderer->gui->movementSpeed);

    renderer->runSlimeCompute(slime->diffuseTexOld, slime->intermediateTex, slimeUnits.x / 8, slimeUnits.y / 8, 1);
    renderer->slimeShader->stop();
}

void Handler::runDiffuseShader() {
    renderer->diffuseShader->start();

    renderer->diffuseShader->loadDiffuseRate(renderer->gui->diffuseRate);
    renderer->diffuseShader->loadDecayRate(renderer->gui->decayRate);

    renderer->runDiffuseCompute(slime->diffuseTexOld, slime->diffuseTexNew, slime->intermediateTex, width, height, 1);

    renderer->diffuseShader->stop();
}