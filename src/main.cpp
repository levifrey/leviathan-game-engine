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
#include "Model.h"

// Globals
float fov = 45.0f;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX;
float lastY;
bool firstMouse = true;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 4.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);	

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
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *=sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f) {
        fov = 1.0f;
    }
    if (fov > 80.0) {
        fov = 80.0f;
    }
}

void cursor_enter_callback(GLFWwindow* window, int entered) {
    if (entered) {
        glfwSetCursorPos(window, 500, 500);
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

void printVector(glm::vec3 vector) {
    std::cout << vector.x << " " << vector.y << " " << vector.z << std::endl;
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
    glClearColor(23.0f/255.0f, 19.0f/255.0f, 19.0f/255.0f, 1.0f);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, 500, 500);
	glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorEnterCallback(window, cursor_enter_callback);
	float cube_vertices[] = {
        // vertex, texture, normal
		// FRONT
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, // top left
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, // top right
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, // bottom right
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, // top left
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, // bottom right
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, // bottom left

		// BACK
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
		-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top right
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom right
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
		-0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom right
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left	
		
		// TOP
		-0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top left
		 0.5f, 0.5f,  0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top right
		 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // top left
		 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
		
		// BOTTOM  	
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // top left
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, // top right
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, // top left
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, // bottom right
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, // bottom left
		
		// LEFT	
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // top left
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, // top right
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom right
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, // top left
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom right
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // bottom left
		
		// RIGHT	
		0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // top left
		0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // top right
		0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
		0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, // top left
		0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f // bottom left
		
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
	Shader myShader("../resources/shaders/test.vert", "../resources/shaders/test.frag");
    Shader lightShader("../resources/shaders/light.vert", "../resources/shaders/light.frag");
    Shader defaultShader("../resources/shaders/default.vert", "../resources/shaders/default.frag");
    
	// Textures
    /*
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
    */
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);	

    Model cube(cube_vertices, sizeof(cube_vertices), cube_indices, sizeof(cube_indices), 8, lightShader);
    cube.makeVertexAttribute(3);
    cube.makeVertexAttribute(2);
    cube.makeVertexAttribute(3);
    cube.addTexture("../resources/textures/container2.jpg");
    Model light(cube_vertices, sizeof(cube_vertices), cube_indices, sizeof(cube_indices), 8, defaultShader);
    light.makeVertexAttribute(3);
    light.makeVertexAttribute(2);
    light.makeVertexAttribute(3);
    glm::vec3 lightPos = glm::vec3(6.0f, 0.0f, 0.0f);
    light.scale(0.4f);
    light.translate(lightPos);
    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        // input 
        processInput(window);
		
		// logic
		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	    projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);			
        //cube.rotate(70.0f * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(100.0f * deltaTime), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::vec3 newVec = glm::vec3(rot * glm::vec4(lightPos, 1.0f));
        light.translate(newVec - lightPos);
        lightPos = newVec;

        // rendering
        Shader* cubeShader = cube.getShader();
        cubeShader->setMat4("view", view);
        cubeShader->setMat4("projection", projection);
        cubeShader->setVec3("viewPos",  cameraPos);
        cubeShader->setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        cubeShader->setFloat("material.shininess", 32.0f);
        cubeShader->setVec3("light.position", lightPos);
        cubeShader->setVec3("light.ambient",  glm::vec3(0.2f, 0.2f, 0.2f));
        cubeShader->setVec3("light.diffuse",  glm::vec3(0.5f, 0.5f, 0.5f));
        cubeShader->setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        cube.render();

        Shader* lightShader = light.getShader();
        lightShader->setMat4("view", view);
        lightShader->setMat4("projection", projection);
        light.render();

        //check events & swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
