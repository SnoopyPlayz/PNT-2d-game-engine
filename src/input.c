#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cglm/cglm.h>
#include "opengl.h"
#include "camera.h"

float lastX = 960, lastY = 540, camRotX = -90.0f, camRotY = 0;
float sensitivity = 0.1f;
bool mouseUsed;

void mouseInput(){
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (!mouseUsed){
		lastX = xpos;
		lastY = ypos;
		mouseUsed = true;
	}

	camRotX += (xpos - lastX) * sensitivity;
        camRotY += (lastY - ypos) * sensitivity;

	lastX = xpos;
        lastY = ypos;

        //camRotY = !(camRotY > 89.0) * camRotY + (camRotY > 89.0) * 89.0;
        //camRotY = !(camRotY < -89.0) * camRotY + (camRotY < -89.0) * -89.0;
        if (camRotY > 89.0)
                camRotY = 89.0;
        if (camRotY < -89.0)
                camRotY = -89.0;

        vec3 direction;
        direction[0] = cos(glm_rad(camRotX)) * cos(glm_rad(camRotY));
        direction[1] = sin(glm_rad(camRotY));
        direction[2] = sin(glm_rad(camRotX)) * cos(glm_rad(camRotY));

        glm_normalize(direction);
        glm_vec3_copy(direction,(float *) camera.front);
}

void keyInput(){
        if (glfwGetKey(window, GLFW_KEY_W)){
		cameraMoveForward();
        };
        if (glfwGetKey(window, GLFW_KEY_S)){
		cameraMoveBack();
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE)){
		cameraMoveUp();
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)){
		cameraMoveDown();
        }
        if (glfwGetKey(window, GLFW_KEY_A)){
		cameraMoveLeft();
        }
        if (glfwGetKey(window, GLFW_KEY_D)){
		cameraMoveRight();
        }
}
