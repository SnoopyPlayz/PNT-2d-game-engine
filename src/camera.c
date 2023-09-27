#include <cglm/cglm.h>
#include <GL/glew.h>
#include "opengl.h"
struct CameraStruct {
	vec3 pos;
 	vec3 front;
	vec3 up;
	vec3 speed;
};

struct CameraStruct camera = {
	{0.0f,1.0f,3.0f},
	{0.0f,0.0f,-1.0f},
	{0.0f,1.0f,0.0f},
	{0.05f,0.05f,0.05f}
};


void cameraDraw(){

	mat4 projection;
	glm_mat4_identity(projection);
	
	glm_perspective(glm_rad(90.0f), (float)screenX / (float)screenY, 0.1f, 100.f, projection);
	sendUniform4f(shaderProgram, "projection", projection);
	
	mat4 view;
	vec3 direction;
	glm_mat4_identity(view);

	glm_vec3_add(camera.front,camera.pos , direction);
	glm_lookat(camera.pos, direction, camera.up, view);
	sendUniform4f(shaderProgram, "view", view);
}

void vec3_mulsub(vec3 a, vec3 b, vec3 dest){
	vec3 result;
	glm_vec3_mul(a, b, result);
	glm_vec3_sub(dest, result, dest);
}

void cameraMoveForward(){
	//		camera.speed + camera.front = camera.pos
	glm_vec3_muladd(camera.speed, camera.front, camera.pos);
}

void cameraMoveBack(){
	//		camera.speed - camera.front = camera.pos
	vec3_mulsub(camera.speed, camera.front, camera.pos);
}

void cameraMoveUp(){
	camera.pos[1] += *camera.speed;
}

void cameraMoveDown(){
	camera.pos[1] -= *camera.speed;
}

void cameraMoveLeft(){
	vec3 result;
	glm_cross(camera.front,camera.up,result);
	glm_normalize(result);
	vec3_mulsub(camera.speed, result, camera.pos);
}

void cameraMoveRight(){
	vec3 result;
	glm_cross(camera.front,camera.up,result);
	glm_normalize(result);
	glm_vec3_muladd(camera.speed,result,camera.pos);
}

