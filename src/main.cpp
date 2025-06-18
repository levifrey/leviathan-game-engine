#include <iostream>
#include "glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"   ourColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;"
    "void main() {\n"
    "	FragColor = vec4(ourColor, 1.0);\n"
    "}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scandcode, int action, int mods) {
    if(key == GLFW_KEY_W && action == GLFW_PRESS) {
        GLint val[2];
        glGetIntegerv(GL_POLYGON_MODE, val);
        if(val[1] == GL_FILL) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            GLint value[2];
            glGetIntegerv(GL_POLYGON_MODE, value);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    
    

}

void createElement(
	float vertices[], 
	size_t vertices_size, 
	unsigned int indices[], 
	size_t indices_size, 
	unsigned int& VAO, 
	unsigned int& VBO, 
	unsigned int& EBO) 
{	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void attributePointer(
	unsigned int& VAO, 
	unsigned int& VBO, 
	unsigned int id, 
	int size, 
	GLenum type, 
	bool normalized, 
	GLsizei stride, 
	const void* offset) 
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(id, size, type, normalized, stride, offset);
	glEnableVertexAttribArray(id);
	glBindVertexArray(0);	
}

int main(int, char**) {

    //initialize
    glfwInit();

    //lock version to > 3.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 800;

    // create window    
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to intialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);

    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	// Test using new functions:
	float test_vertices[] = {
		// positions     // colors
		-0.5,  0.5, 0.0, 1.0, 0.0, 0.0, // top left
		 0.5,  0.5, 0.0, 0.0, 1.0, 0.0, // top right
		 0.5, -0.5, 0.0, 0.0, 0.0, 1.0, // bottom right
		-0.5, -0.5, 0.0, 1.0, 1.0, 1.0  // bottom left
	};

	unsigned int test_indices[] = {
		0, 1, 2, // upper right triangle
		0, 2, 3  // lower left triangle
	};

	unsigned int test_VBO, test_VAO, test_EBO;

	createElement(test_vertices, sizeof(test_vertices), test_indices, sizeof(test_indices), test_VAO, test_VBO, test_EBO);
	attributePointer(test_VAO, test_VBO, 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	attributePointer(test_VAO, test_VBO, 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		 	

    //create new vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //test if vertex shader compilation was successful
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
    }

    //create new frag shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //test if fragment shader compilation was successful
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << infoLog << std::endl;
    }

    //create shader program with the vertex and fragment shader
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //check if linking was successful
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_ERROR" << infoLog << std::endl;
    }

    glUseProgram(shaderProgram);

    //remove shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Textures
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);


    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        //input 
        processInput(window);

        //rendering 

        glUseProgram(shaderProgram);

		glBindVertexArray(test_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, test_EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //check events & swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

