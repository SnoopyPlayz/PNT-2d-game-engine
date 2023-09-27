#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <cglm/cglm.h>
#include "opengl.h"
#include "fileLoad.h"
#include "shader.h"
#include "camera.h"
#include "input.h"

int rot = 0;
void update(){
	glfwPollEvents();
	keyInput();
	mouseInput();
	rot += 1;
}

unsigned int texture1 = 0;
unsigned int texture = 0;
Model car = (Model) {};
Model cube = (Model) {};

void render(){
	glClearColor(0.1f,0.1f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cameraDraw();

	drawModel(car, texture1, (vec3) {9,0,-10}, (vec3) {0, 1, 2});

	drawModel(cube, texture, (vec3) {0,rot,10}, (vec3) {0,0,-10});

	glfwSwapBuffers(window);
}

int main(){
	openglInit();

	shaderProgram = createShaderProgram("vertexShader.sh","fragmentShader.sh");
	glUseProgram(shaderProgram);

	texture = loadTexture("../model/redd.png");
	texture1 = loadTexture("../model/awesomeface.png");

   	car = loadModel("../model/Racing_Bros_car.ply");
   	cube = loadModel("../model/face.ply");

	double timePerFrame = 1./60.; 

	double currentTime = glfwGetTime();
	double accumulator = 0.0;

	int FPSTimes = 0;
	int FPSOldtime = 0;

	while (!glfwWindowShouldClose(window)) {
		double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;

		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= timePerFrame) {
			update();
			accumulator -= timePerFrame;
		}
		render();

		FPSTimes += 1;
		if (newTime - FPSOldtime > 1.0){
			char FPSstring[23];
			sprintf(FPSstring, "KNK   FPS: %d", FPSTimes);
			glfwSetWindowTitle(window, FPSstring);

			FPSTimes = 0;
			FPSOldtime = newTime;
		}
	}
	glfwTerminate();
}

