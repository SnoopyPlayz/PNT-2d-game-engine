clear
time sudo clang -target x86_64-pc-win32 -g hello.c shader.c fileLoad.c opengl.c -o winhello.exe -I/usr/x86_64-w64-mingw32/include -L/usr/x86_64-w64-mingw32/lib -Wall  -I../cglwin/cglm/include -lGLEW -lglfw -lGL -lm -D__USE_MINGW_ANSI_STDIO=1 -ferror-limit=500
