#pragma once
struct CameraStruct {
	vec3 pos;
	vec3 front;
	vec3 up;
	vec3 speed;
};
extern struct CameraStruct camera; 

void cameraDraw();


void cameraMoveForward();

void cameraMoveBack();

void cameraMoveDown();

void cameraMoveUp();

void cameraMoveRight();

void cameraMoveLeft();
