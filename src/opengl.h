#pragma once
#include <GLFW/glfw3.h>
#include "fileLoad.h"

extern unsigned int shaderProgram;
extern GLFWwindow* window;
extern int screenX, screenY;

void drawModel(Texture * Texture, int x, int y);
void openglInit();
