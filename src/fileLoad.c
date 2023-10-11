#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "opengl.h"

unsigned int loadTexture(char* fileLocation, int * width, int * height) {
	stbi_set_flip_vertically_on_load(1);

 	int nrChannels;
 	unsigned char *data = stbi_load(fileLocation, width, height, &nrChannels, 0);
	 
 	if (!data){
 		printf("error loading image file: %s",fileLocation);
 		return 0;
 	}
	 
	unsigned int texture;
	glGenBuffers(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *width, *height, 0, GL_RGBA * (nrChannels == 4) + GL_RGB * (nrChannels == 3), GL_UNSIGNED_BYTE,data);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	return texture;
}

/*
typedef struct Texture {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	int numIndices;
	unsigned int texture;
	int width;
	int height;
} Texture;*/

Texture loadImage2d(char * texturePath, int x, int y){
	int texWidth, texHeight;
	unsigned int texture = loadTexture(texturePath, &texWidth, &texHeight);
	
	int screenX,screenY; //screen size
	glfwGetWindowSize(window, &screenX, &screenY);

	//image size
	texWidth +=x ;
	texHeight += y;
	float sizeX = texWidth / ((float)screenX * 0.52);
	float sizeY = texHeight / (-(float)screenY * 0.52);

	float vert[] = {
		//  texture od 0px do 1000+px --> opengl od -1 do 1
		sizeX,  0.0f,		1.0f,1.0f, //top right
		sizeX,  sizeY,		1.0f,0.0f, //bottom right
		0.0f,   sizeY,		0.0f,0.0f, //bottom left
		0.0f, 0.0f,		0.0f,1.0f , //top left
	};

	int inds[] = {
		0, 1, 3,
		1, 2, 3
	};

	int vertSize = sizeof(vert);
	int indsSize = sizeof(inds);

	//	Buffer texture
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
 
        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertSize, vert, GL_STATIC_DRAW);
 
        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indsSize, inds, GL_STATIC_DRAW);
	//pos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	//tex
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	

	return (Texture) {VAO,VBO,EBO,indsSize,texture,texWidth,texHeight,0};
}
