#include "ShaderLoader.h"
#include <iostream>
#include <fstream>

unsigned int compileShader(const std::filesystem::path& path, GLenum type) {
    std::ifstream file;
    std::stringstream stream;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    file.open(path.string());
    stream << file.rdbuf();
    file.close();
    std::string codeString = stream.str();
    const char* code = codeString.c_str();

    unsigned int id;
    int success;
    char infoLog[512];
    id = glCreateShader(type);
    glShaderSource(id, 1, &code, NULL);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout 
            <<"ERROR::SHADER::COMPILATION::COMPILATION_FAILED (" 
            << path.string() 
            << ")" 
            << std::endl;
        std::cerr
            << infoLog
            << std::endl;
    }
    return id;
}

Shader ShaderLoader::loadShaderFromFile(
        const std::filesystem::path& vertex_path, 
        const std::filesystem::path& fragment_path,
        const std::filesystem::path& geometry_path) {
    unsigned int ID = glCreateProgram();
    unsigned int vertexID;
    unsigned int geometryID;
    unsigned int fragmentID;
    vertexID = compileShader(vertex_path, GL_VERTEX_SHADER);
    glAttachShader(ID, vertexID);
    if (!geometry_path.empty()) {
        geometryID = compileShader(geometry_path, GL_GEOMETRY_SHADER);
        glAttachShader(ID, geometryID);
    }
    fragmentID = compileShader(fragment_path, GL_FRAGMENT_SHADER);
    glAttachShader(ID, fragmentID);

    glLinkProgram(ID);
    
    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout
            << "ERROR::SHADER::PROGRAM::LINKING_FAILURE"
            << std::endl
            << infoLog
            << std::endl;
    }

    glDeleteShader(vertexID);
    if (!geometry_path.empty()) {
        glDeleteShader(geometryID);
    }
    glDeleteShader(fragmentID);

    return {ID};
}


/*
Shader ShaderLoader::loadShaderFromFile(
        const std::filesystem::path& vertex_path, 
        const std::filesystem::path& fragment_path) 
{
    unsigned int ID;
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        vShaderFile.open(vertex_path.string());
        fShaderFile.open(fragment_path.string());
        std::stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = getTextFromFile(vertex_path);
        fragmentCode = getTextFromFile(fragment_path);
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
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION::COMPILATION_FAILED (" << vertex_path.string() << ")" << std::endl;
        std::cerr << infoLog << std::endl;
    }


    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED (" << fragment_path.string() << ")" << std::endl;
        std::cerr << infoLog << std::endl;
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
    
    return {ID};
}
*/
