# computer_graphics
Computer Graphics lab in OpenGL (Visual Studio, C++)
# Having ready project:
Do not need to run Visual Studio, go to Debug and run .exe

# reating new project:
Download 'Glew and Glut'
Create MVS Windows32 Cpp Project, copy .cpp file
Copy glut32.dll to C:\Windows\SysWOW64  (or System32, depends what version)
Project -> Properties -> C/C++ -> General -> Additional Include Directories -> Glew and Glut\glew-1.11.0\include
Project -> Properties -> Linker -> General -> Additional Include Libraries -> Glew and Glut\glew-1.11.0\lib
Project -> Properties -> Linker -> Input -> Additional Dependencies -> glew32.lib