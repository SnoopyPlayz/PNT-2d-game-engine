clear
time clang -g hello.c shader.c input.c fileLoad.c camera.c opengl.c -o hello.exe -Wall -lcglm -lGLEW -lglfw -lGL -lm && ./hello.exe
