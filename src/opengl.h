#pragma once
#include <GLFW/glfw3.h>
#include "fileLoad.h"

extern unsigned int shaderProgram;
extern GLFWwindow* window;
extern int screenX, screenY;

int colisionBox(int x, int y, int width, int height);
int drawMenu(Texture * t);
void drawModel(Texture * t);
int openglInit();
