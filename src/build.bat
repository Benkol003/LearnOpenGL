cd ../bin/
call "D:\Program Files\Microsoft Visual Studio\Community\VC\Auxiliary\Build\vcvars64.bat"
cl /I..\lib /std:c++17 /EHsc /W4 /MT gdi32.lib user32.lib shell32.lib opengl32.lib ..\lib\glfw-3.3.6\lib-vc2022\glfw3_mt.lib ..\lib\glew-2.1.0\lib\Release\x64\glew32s.lib ../src/main.cpp
main.exe