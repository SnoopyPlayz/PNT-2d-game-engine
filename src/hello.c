#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "opengl.h"
#include "fileLoad.h"
#include "shader.h"
#include "Gscenes.h"

Texture cube = (Texture) {};
Texture play = (Texture) {};

enum GameState{
	menu,
	pause,
	game,
};
enum GameState gameState = menu;


void updateMenu(){
	if (drawMenu(&play, CLICK))
		gameState = game;
}

void updateGame(){
	updateScene();
}

void updatePause(){
}

void update(){
	glfwPollEvents();
	glClearColor(0.1f,0.1f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	switch (gameState) {
		case game:
			updateGame();
			break;
		case menu:
			updateMenu();
			break;
		case pause:
			updatePause();
			break;
	}
	glfwSwapBuffers(window);
}
void initGame(){
	initScene();
}

int main(){
	openglInit();
	initGame();

   	play = loadImage2d("../res/menu.png",800,100);

	//loop
	double timePerFrame = 1./60.; 

	double currentTime = glfwGetTime();

	int FPSTimes = 0;
	double FPSOldtime = 0;
	double delta = 0.;

	while (!glfwWindowShouldClose(window)) {
		double newTime = glfwGetTime();
		delta += (newTime - currentTime) / timePerFrame;
		currentTime = newTime;

		while (delta >= 1) {
			update();
			delta -= 1;

			//FPS counter
			FPSTimes += 1;	
			if (newTime - FPSOldtime > 1.0){
				char FPSstring[23];
				sprintf(FPSstring, "PNT FPS: %d", FPSTimes);
				glfwSetWindowTitle(window, FPSstring);

				FPSTimes = 0;
				FPSOldtime = newTime;
			}
		}
	}
	glfwTerminate();
}
