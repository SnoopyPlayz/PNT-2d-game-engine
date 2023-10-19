#include "opengl.h"
#include "fileLoad.h"
#include <stdio.h>

struct Texture Scenes[3] = {{},{},{}};
Texture nextButton = (Texture) {};


int currentScene;
void updateScene(){
	nextButton.x = 1520;
	if (currentScene > 0 && colisionTex(&nextButton))
		currentScene--;

	nextButton.x = 0;
	if (currentScene < 2 && colisionTex(&nextButton))
		currentScene++;
}

void renderScene(){
	drawModel(&Scenes[currentScene]);

	nextButton.x = 1520;
	if (currentScene > 0)
		drawModel(&nextButton);

	nextButton.x = 0;
	if (currentScene < 2)
		drawModel(&nextButton);

}
void initScene(){
	Scenes[0] = loadStrechedImage("../res/Right.png",100,0,0,0);
   	Scenes[1] = loadStrechedImage("../res/room2.png",100,0,0,0);
	Scenes[2] = loadStrechedImage("../res/Left.png",100,0,0,0);
	nextButton = loadStrechedImage("../res/nextButton.png",-100,-100,1520,400);
	nextButton.z = 0.3;
}
