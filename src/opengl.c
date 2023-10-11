#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "fileLoad.h"
#include "shader.h"

int screenX, screenY;
unsigned int shaderProgram = 0;
GLFWwindow* window = 0;


typedef float Vec3[3];
unsigned int ShaderPosUniform = 0;

void drawModel(Texture * t, int x, int y){
	
/*
		 ^			     ^
	opengl	 |			     |	silnik
	-1 <-----|------> 1 	<---   0 <---|----> 1920
		 |			     |
		\/			    \/
*/
	float Posx = (2.0f * (float)x) / screenX - 1.0f; //(Muj kod) zamienia od 0 do 1920 na -1 do 1 dla opengl
	float Posy = (2.0f * (float)(y * -1)) / screenY + 1.0f; 
	
	glUniform3fv(ShaderPosUniform, 1, (Vec3) {Posx,Posy,0});

	glBindVertexArray(t->VAO);

	glBindTexture(GL_TEXTURE_2D, t->texture);
	glDrawElements(GL_TRIANGLES, t->numIndices, GL_UNSIGNED_INT, 0);
}

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
	glCullFace(GL_FRONT);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// shader
	shaderProgram = createShaderProgram("vertexShader.sh","fragmentShader.sh");
	glUseProgram(shaderProgram);
	ShaderPosUniform = glGetUniformLocation(shaderProgram, "pos");

	return 0;
}
