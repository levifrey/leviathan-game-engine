#include <iostream>
#include "../include/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
#include "Shader.h"

// Globals
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);	
float yaw = -90.0f;
float pitch = 0.0f;


float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
	const float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	std::cout << xpos << std::endl;
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
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEIGHT = 1000;
	
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
	glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	// Test using new functions:
	float test_vertices[] = {
		// positions     // colors      // tex coords
		-0.5,  0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, // top left
		 0.5,  0.5, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0, // top right
		 0.5, -0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, // bottom right
		-0.5, -0.5, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0 // bottom left
	};

	unsigned int test_indices[] = {
		0, 1, 2, // upper right triangle
		0, 2, 3  // lower left triangle
	};
	unsigned int test_VBO, test_VAO, test_EBO;

	createElement(test_vertices, sizeof(test_vertices), test_indices, sizeof(test_indices), test_VAO, test_VBO, test_EBO);
	attributePointer(test_VAO, test_VBO, 0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	attributePointer(test_VAO, test_VBO, 1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	attributePointer(test_VAO, test_VBO, 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));

	float cube_vertices[] = {
		// FRONT
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top left
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top left
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom left

		// BACK
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // top left
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // top right
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom right
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // top left
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom right
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  // bottom left	
		
		// TOP
		-0.5f, 0.5f,  0.5f, 0.0f, 1.0f, // top left
		 0.5f, 0.5f,  0.5f, 1.0f, 1.0f, // top right
		 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, 0.5f,  0.5f, 0.0f, 1.0f, // top left
		 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f,  // bottom left
		
		// BOTTOM  	
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top left
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // top right
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top left
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  // bottom left
		
		// LEFT	
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // top left
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // top right
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // top left
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,  // bottom left
		
		// RIGHT	
		0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top left
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // top right
		0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom right
		0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // top left
		0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // bottom right
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f  // bottom left
		
	};
	unsigned int cube_indices[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26, 
		27, 28, 29,
		30, 31, 32,
		33, 34, 35
	};
	unsigned int cube_VBO, cube_VAO, cube_EBO;
	
	createElement(cube_vertices, sizeof(cube_vertices), cube_indices, sizeof(cube_indices), cube_VAO, cube_VBO, cube_EBO);
	attributePointer(cube_VAO, cube_VBO, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	attributePointer(cube_VAO, cube_VBO, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
 	
	Shader myShader("../resources/shaders/test.vert", "../resources/shaders/test.frag");
    
	// Textures
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../resources/textures/container.jpg", &width, &height, &nrChannels, 0);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
    	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    	glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture" << std::endl;
	}
    stbi_image_free(data);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);			
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        // input 
        processInput(window);
		
		// logic
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		model = glm::rotate(model, glm::radians(70.0f * deltaTime), glm::vec3(1.0f, 1.0f, 0.0f));	
	
        // rendering 
        glUseProgram(myShader.ID);
		int modelLoc = glGetUniformLocation(myShader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));	    
		int viewLoc = glGetUniformLocation(myShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		int projLoc = glGetUniformLocation(myShader.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(cube_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube_EBO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		int mode = glfwGetInputMode(window, GLFW_CURSOR);
        //check events & swap buffers
        glfwSwapBuffers(window);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
