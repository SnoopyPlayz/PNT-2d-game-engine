#pragma once
#include <GLFW/glfw3.h>
#include "fileLoad.h"

extern unsigned int shaderProgram;
extern GLFWwindow* window;
extern int screenX, screenY;

void drawModel(Model, unsigned int texture, vec3 rotation, vec3 position);
void sendUniform4f(int shaderProgram, char * name, mat4 data);
void openglInit();
