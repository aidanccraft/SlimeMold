#include <fstream>
#include <string>
#include <sstream>

#include "Shader.h"

Shader::Shader(ShaderType shaderType, const std::string& key) {
    const std::string shader_path = "res/shaders/";
    this->shaderType = shaderType;
    
    if (shaderType == ShaderType::COMPUTE) {
        std::string computeSource = parseShaders(shader_path + key + ".comp.glsl");
        createComputeShader(computeSource);
    } else if (shaderType == ShaderType::VERTFRAG) {
        std::string vertSource = parseShaders(shader_path + key + ".vert.glsl");
        std::string fragSource = parseShaders(shader_path + key + ".frag.glsl");
        createFragVertShader(vertSource, fragSource);
    }
}

Shader::~Shader() {
    cleanUp();
}

std::string Shader::parseShaders(const std::string& compPath) {
    std::ifstream compStream(compPath);

    std::string line;
    std::stringstream ss;
    while (getline(compStream, line)) {
        ss << line << '\n';
    }

    return ss.str();
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : (type == GL_FRAGMENT_SHADER ? "fragment" : "compute")) << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::createComputeShader(const std::string& computeShader) {
    programID = glCreateProgram();
    computeShaderID = compileShader(GL_COMPUTE_SHADER, computeShader);

    glAttachShader(programID, computeShaderID);
    glLinkProgram(programID);
    glValidateProgram(programID);

    return programID;
}

unsigned int Shader::createFragVertShader(const std::string& vertexShader, const std::string& fragmentShader) {
    programID = glCreateProgram();
    vertexShaderID = compileShader(GL_VERTEX_SHADER, vertexShader);
    fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    glValidateProgram(programID);

    return programID;
}

inline void Shader::getAllUniformLocations() {}

void Shader::start() {
    glUseProgram(programID);
}

void Shader::dispatch(int x, int y, int z) {
    glDispatchCompute((GLuint)x, (GLuint)y, (GLuint)z);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void Shader::stop() {
    glUseProgram(0);
}

void Shader::cleanUp() {
    stop();
    if (shaderType == ShaderType::COMPUTE) {
        glDetachShader(programID, computeShaderID);
        glDeleteShader(computeShaderID);
    } else if (shaderType == ShaderType::VERTFRAG) {
        glDetachShader(programID, vertexShaderID);
        glDetachShader(programID, fragmentShaderID);
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }
    glDeleteProgram(programID);
}

void Shader::loadInt(unsigned int location, const int value) {
    glUniform1i(location, value);
}

void Shader::loadFloat(unsigned int location, const float value) {
    glUniform1f(location, value);
}

void Shader::loadBool(unsigned int location, const bool value) {
    if (value)
        glUniform1i(location, 1);
    else
        glUniform1i(location, 0);
}

void Shader::loadVec2f(unsigned int location, const glm::vec2& vector) {
    glUniform2f(location, vector.x, vector.y);
}

void Shader::loadVec4f(unsigned int location, const glm::vec4& vector) {
    glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}