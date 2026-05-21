#include "Shader.h"

void Shader::use() const {
    glUseProgram(ID_);
}

void Shader::setBool(const std::string &name, bool value) const {
    int location = glGetUniformLocation(ID_, name.c_str());
    glUniform1i(location, (int)value);
}

void Shader::setInt(const std::string &name, int value) const {
    int location = glGetUniformLocation(ID_, name.c_str());
    glUniform1i(location, value);
}

void Shader::setFloat(const std::string &name, float value) const {
    int location = glGetUniformLocation(ID_, name.c_str());
    glUniform1f(location, value);
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const {
    int location = glGetUniformLocation(ID_, name.c_str());
    glUniform3fv(location, 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const {
    int location = glGetUniformLocation(ID_, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec4(const std::string &name, glm::vec4 value) const {
    int location = glGetUniformLocation(ID_, name.c_str());
    glUniform4fv(location, 1, glm::value_ptr(value));
}
