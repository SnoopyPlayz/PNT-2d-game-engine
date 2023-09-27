#pragma once
typedef struct Model {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	int numIndices;
} Model;
unsigned int loadTexture(char * fileLocation);
Model loadModel(char * fileLocation);
