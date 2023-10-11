clear
files="hello.c shader.c fileLoad.c opengl.c"
args="-Wall -lGLEW -lglfw -lGL -lm"

time clang -g $files -o hello.exe $args && ./hello.exe
