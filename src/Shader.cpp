#include "Shader.h"
#include <iostream>
#include <stdexcept>

void uniformFound( const std::string& name, int location) {
    if (location == -1) {
        throw std::runtime_error("ENGINE ERROR: could not set uniform: " + name); 
    }
}

Shader::Shader(const char* vertexPath, const char* fragmentPath) {

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } 
    catch(std::ifstream::failure e) {
        std::cout << "FAILED TO READ FROM FILE" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION::COMPILATION_FAILED (" << vertexPath << ")" << std::endl;
    }


    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED (" << fragmentPath << ")" << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILURE" << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    use();
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const {
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform1i(location, (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string &name, float value) const {
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform1f(location, value);
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const {
    int location = glGetUniformLocation(ID, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const {
    int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) { std::cout << "Error setting variable: " << name << std::endl; }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::reserveTexture(const std::string &var_name, int texture_num) {
    setInt(var_name, texture_num);
}
