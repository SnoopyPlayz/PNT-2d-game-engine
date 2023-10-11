#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>
#include "opengl.h"
#include "fileLoad.h"
#include "shader.h"

float rot = 0;
double cursorX,cursorY;
void update(){
	glfwPollEvents();
	
	
	glfwGetCursorPos(window,&cursorX,&cursorY);

	//keyInput();
	//mouseInput();
	rot += 10;
	if (rot > 1900){
		rot = 0;
	};
}

Texture car = (Texture) {};
Texture cube = (Texture) {};
Texture menu = (Texture) {};
Texture room = (Texture) {};
int drawMenu(Texture * t, int x, int y){
	drawModel(t, x, y);

	int screenX,screenY; //screen size
	glfwGetWindowSize(window, &screenX, &screenY);
	

	// zmien kolizie menu w zależności od rezolucji okienka
	
	float scaleX =  (((float)screenX * 0.5) / t->width)*0.5;
	float scaleY =  ((float)screenY * 0.5) / t->height;

	if (cursorX < t->width * scaleX + x && cursorX > x 
			&& cursorY < t->height * scaleY + y && cursorY > y 
			&& glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)){
		return 1;
	}
	return 0;
}

int menuon=0;
void render(){
	glClearColor(0.1f,0.1f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	drawModel(&car, cursorX, cursorY);
	drawModel(&room, 0, 0);


	if (!menuon){
		if (drawMenu(&menu, 800, 100)){
			menuon=1;
			printf("%s %d \n", "menu dziala",(int)glfwGetTime());
		}
	}else {
		drawModel(&car, 0, 900);
		drawModel(&car, 200, 900);
	}

	glfwSwapBuffers(window);
}

int main(){
	openglInit();

   	car = loadImage2d("../res/awesomeface.png",0,0);
   	cube = loadImage2d("../res/container.jpg",0,0);
   	menu = loadImage2d("../res/menu.png",0,0);
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

