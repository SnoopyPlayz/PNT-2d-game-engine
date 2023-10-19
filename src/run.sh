clear
files="Gscenes.c hello.c shader.c fileLoad.c opengl.c"
args="-Wall -lGLEW -lglfw -lGL -lm"

time clang $files -o hello.exe $args && ./hello.exe
