#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "opengl.h"
#include "fileLoad.h"
#include "shader.h"

double cursorX,cursorY;
void update(){
	glfwPollEvents();
	
	glfwGetCursorPos(window,&cursorX,&cursorY);
}

Texture car = (Texture) {};
Texture cube = (Texture) {};
Texture menu1 = (Texture) {};
Texture room = (Texture) {};

enum GameState{
	menu,
	pause,
	game,
};
enum GameState gameState = menu;

void renderMenu(){
	if (drawMenu(&menu1, 800, 100)){
		gameState = game;
		printf("%s %d \n", "menu dziala",(int)glfwGetTime());
	}
}

void renderGame(){
	drawModel(&room, 0, 0);
	drawModel(&car, 0, 900);
	drawModel(&car, 200, 900);
}

void renderPause(){
}

void render(){
	glClearColor(0.1f,0.1f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawModel(&car, cursorX, cursorY);

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

   	car = loadImage2d("../res/awesomeface.png",0,0);
   	cube = loadImage2d("../res/container.jpg",0,0);
   	menu1 = loadImage2d("../res/menu.png",0,0);
   	room = loadImage2d("../res/room2.png",100,0);

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
			sprintf(FPSstring, "PNC    FPS: %d", FPSTimes);
			glfwSetWindowTitle(window, FPSstring);

			FPSTimes = 0;
			FPSOldtime = newTime;
		}
	}
	glfwTerminate();
}

