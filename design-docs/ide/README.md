
# Design Document
This folder contains design related documentation.

# Status Quo
- Visual Studio: It's a very good IDE, while using his own project manager. With CMake its tedious to mantain files.. It's biggest advantage it is debugger. Sometimes, it slowdowns even with plenty of memory and cpu cores available.
- Qt Creator: Excellent for Qt application development. Is tedious to add or modify files (while using CMake). Its syntax coloring highligther supports Doxygen special comments.
- Code::Blocks: Supports many platforms and compilers. Last time checked, its CMake integration doesn't supports debugging.
- Eclipse:
- IntelliJ IDEA: 

Why CMake is important? Using CMake as a base build system it's a must, because is becoming the standard to build C/C++ projects, so supporting it is essential.
