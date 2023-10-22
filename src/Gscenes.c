#include <stdio.h>
#include "opengl.h"
#include "fileLoad.h"

Texture nextButton = (Texture) {};
Texture cameraImage = (Texture) {};
Texture Scenes[3];
Texture cctvScenes[4];

int sizeScenes = sizeof(Scenes) / sizeof(Scenes[0]);
int sizeCctvSc = sizeof(cctvScenes) / sizeof(cctvScenes[0]);

int currentScene = 1;
int cctvOrCamera;

void drawButtons(int lastScene){
	nextButton.x = 1520;
	if (currentScene > 0 && drawMenu(&nextButton, CLICK))
		currentScene--;

	nextButton.x = 0;
	// TODO FIX THIS CODE !!!!!!! (1)
	if (currentScene < lastScene - 1 && drawMenu(&nextButton, CLICK))
		currentScene++;

	//printf("%d \n",currentScene);
	//printf("S: %d \n",lastScene);
}

void updateCameraScene(){
	drawButtons(sizeScenes);

	if (currentScene == 1 && drawMenu(&cameraImage, CLICK)){
		cctvOrCamera = 1;
		/*
		double cursorX,cursorY;
		glfwGetCursorPos(window,&cursorX,&cursorY);
		cursorY *= 1080. / screenY;
		cursorX *= 1920. / screenX;

		cameraImage.x = (int) cursorX - 50;
		cameraImage.y = (int) cursorY - 100;
		printf("x: %d \n", cameraImage.x);
		printf("y: %d \n", cameraImage.y);
		*/
	}
	drawModel(&Scenes[currentScene]);
}

void updateCctvScene(){
	drawButtons(sizeCctvSc);

	if (currentScene == 1 && drawMenu(&cameraImage, CLICK)){
		cctvOrCamera = 0;
	}

	drawModel(&cctvScenes[currentScene]);
}

void updateScene(){
	if (cctvOrCamera){
		updateCctvScene();
	}else{
		updateCameraScene();
	}
}

//TODO FIX CODE
void initScene(){

	for (int i = 0; i < sizeScenes; i++) {
		char fileLoc[30];
		sprintf(fileLoc,"../res/cctvCam/SCENE%d.png",i);
		Scenes[i] = loadStrechedImage(fileLoc,100,0,0,0);
		Scenes[i].z = 0.8;
	}
	for (int i = 0; i < sizeCctvSc; i++) {
		char fileLoc[30];
		sprintf(fileLoc,"../res/cctvCam/CCTV%d.png",i);
		cctvScenes[i] = loadStrechedImage(fileLoc,100,0,0,0);
		cctvScenes[i].z = 0.8;
	}
	nextButton = loadStrechedImage("../res/nextButton.png",-100,-100,1520,400);
	nextButton.z = 0.3;
	cameraImage = loadImage2d("../res/camera.png",746, 391);
	cameraImage.z = 0.1;
}
