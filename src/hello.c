#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "opengl.h"
#include "fileLoad.h"
#include "shader.h"

double cursorX,cursorY;
void update(){
	glfwPollEvents();
	
	glfwGetCursorPos(window,&cursorX,&cursorY);
}

Texture face = (Texture) {};
Texture cube = (Texture) {};
Texture play = (Texture) {};
Texture room = (Texture) {};
Texture nextButton = (Texture) {};

enum GameState{
	menu,
	pause,
	game,
};
enum GameState gameState = menu;


void renderMenu(){
	if (drawMenu(&play))
		gameState = game;

}

void renderGame(){

	drawModel(&room);
	drawModel(&face);
	drawModel(&face);

	if (drawMenu(&nextButton))
		gameState = game;
}

void renderPause(){
}

void render(){
	glClearColor(0.1f,0.1f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	face.x = cursorX, face.y = cursorY;

	drawModel(&face);

	switch (gameState) {
		case game:
			renderGame();
			break;
		case menu:
			renderMenu();
			break;
		case pause:
			renderPause();
			break;
	}
	glfwSwapBuffers(window);
}

int main(){
	openglInit();

	//Texture *array = (Texture *)malloc(sizeof(Texture));

   	face = loadImage2d("../res/awesomeface.png",0,0,0,0);
   	cube = loadImage2d("../res/container.jpg",0,0,0,0);
   	play = loadImage2d("../res/menu.png",0,0,800,100);
   	room = loadImage2d("../res/room2.png",100,0,0,0);
   	nextButton = loadImage2d("../res/nextButton.png",-100,-100,1520,400);

	//loop
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
	glfwTerminate();
}

