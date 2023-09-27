#include <cglm/cglm.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "fileLoad.h"

// OPENGL INIT
unsigned int shaderProgram = 0;
GLFWwindow* window = 0;

void sendUniform4f(int shaderProgram, char * name, mat4 data){
        int uniformLoc = glGetUniformLocation(shaderProgram, name);
        glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, (const float *) data);
}

void drawModel(Model m, unsigned int texture, vec3 rotation, vec3 position){
	mat4 model;
        glm_mat4_identity(model);

	glm_translate(model, position);
	glm_rotate_x(model, glm_rad(rotation[0]), model);
	glm_rotate_y(model, glm_rad(rotation[1]), model);
	glm_rotate_z(model, glm_rad(rotation[2]), model);

	sendUniform4f(shaderProgram, "model", model);

	glBindVertexArray(m.VAO);
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glDrawElements(GL_TRIANGLES, m.numIndices, GL_UNSIGNED_INT, 0);
}

int screenX, screenY;
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
        screenX = width;
        screenY = height;
        glViewport(0, 0, width, height);
}

void openglError(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
        printf("Opengl Error %s \n", message);
}

int openglInit(){
	if (!glfwInit())
        	return -1;

        window = glfwCreateWindow(800, 600, "KNK", NULL, NULL);

        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK)
                return -1;

        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(openglError, 0);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return 0;
}
