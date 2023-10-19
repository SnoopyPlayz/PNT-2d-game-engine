clear
time sudo zig cc -target x86_64-windows -g Gscenes.c hello.c shader.c fileLoad.c opengl.c -o winhello.exe -I/usr/x86_64-w64-mingw32/include -L/usr/x86_64-w64-mingw32/lib -Wall  -I../glew-2.2.0/include -L../glew-2.2.0/lib -lglew32 -lglfw3 -lopengl32 -lm -D__USE_MINGW_ANSI_STDIO=1 -ferror-limit=500
