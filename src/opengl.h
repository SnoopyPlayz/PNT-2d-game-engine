#pragma once
#include <GLFW/glfw3.h>
#include "fileLoad.h"

extern unsigned int shaderProgram;
extern GLFWwindow* window;
extern int screenX, screenY;

#define HOLD 1
#define CLICK 0
int colisionBox(int x, int y, int width, int height, int dragOrClick);
int drawMenu(Texture * t, int dragOrClick);
void drawModel(Texture * t);
int openglInit();
