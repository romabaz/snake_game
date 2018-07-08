How to build Snakey for Windows

# Prerequisites:
1. SDL2 (http://libsdl.org/download-2.0.php)
2. CMake for Windows
3. MS Visual Studio

# Generate MS Visual Studio project
1. Open file CMakeLists.txt and set correct path for SDL2 directory
2. cmake CMakeLists.txt

# Compile and run
1. Open generated solution in MS Visual Studio
2. Click Build
3. Copy SDL2.dll into generated folder bin/Debug