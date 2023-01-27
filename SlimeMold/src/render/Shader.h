#pragma once

#include "Global.h"

enum class ShaderType {
    VERTFRAG, COMPUTE
};

class Shader {
private:
    unsigned int computeShaderID = 0;
    unsigned int vertexShaderID = 0;
    unsigned int fragmentShaderID = 0;

    ShaderType shaderType;

    std::string parseShaders(const std::string& computePath);
    unsigned int compileShader(unsigned int type, const std::string& source);
    unsigned int createFragVertShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int createComputeShader(const std::string& computeShader);

protected:
    unsigned int programID = 0;

    virtual void getAllUniformLocations() = 0;
public:
    Shader(ShaderType shaderType, const std::string& key);
    ~Shader();

    void start();
    void dispatch(int x, int y, int z);
    void stop();
    void cleanUp();

    void loadInt(unsigned int location, const int value);
    void loadFloat(unsigned int location, const float value);
    void loadBool(unsigned int location, const bool value);
    void loadVec2f(unsigned int location, const glm::vec2& vector);
    void loadVec4f(unsigned int location, const glm::vec4& vector);
};