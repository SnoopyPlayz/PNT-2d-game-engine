#include <stdio.h>
#include <string.h>
#include "GLbindings.h"

void shaderError(unsigned int vertexShader){
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success){
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("vertex compilation failed %s \n",infoLog);
	}
}

unsigned int compileShader(unsigned int shaderType,const char ** shaderSource){
	unsigned int shader;
	shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, shaderSource, NULL);
	glCompileShader(shader);
	shaderError(shader);
	return shader;
}

unsigned int createShader(unsigned int shaderType,char * filePath){
	FILE * shaderfile;

	shaderfile = fopen(filePath,"r");

	if (!shaderfile){
		printf("no shader file");
		return 0;
	}

	char readline[100];
	char allLines[1000] = "";

	while (fgets(readline, 100, shaderfile)){
		strcat(allLines,readline);	
	};
	fclose(shaderfile);

	const char * shaderSource = allLines;
	return compileShader(shaderType,&shaderSource);
}

unsigned int createShaderProgram(char * vertexFilePath, char * fragmentFilePath){
	unsigned int vertexShader = createShader(GL_VERTEX_SHADER,vertexFilePath);
	unsigned int fragmentShader = createShader(GL_FRAGMENT_SHADER,fragmentFilePath);

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram,vertexShader);
	glAttachShader(shaderProgram,fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
