cmake_minimum_required(VERSION 3.10)
project(Snakey)

set(CMAKE_SUPPRESS_REGENERATION true)
set(CMAKE_BINARY_DIR ./bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 11)

set(SDL2_LIB_DIR "d:/dev/C/SDL2-2.0.4")
#set(SDL2_LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SDL2-2.0.4")
set(SDL2_INCLUDE_DIRS "${SDL2_LIB_DIR}/include")
include_directories(${SDL2_INCLUDE_DIRS})

add_library(sdl2 STATIC IMPORTED)
add_library(sdl2main STATIC IMPORTED)

add_executable(Snakey
		"src/Food.cpp"
		"src/GameTexture.cpp"
		"src/GameWorld.cpp"
        "src/Snakey.cpp"
        "src/main.cpp"
		"src/include/Food.h"
		"src/include/GameTexture.h"
		"src/include/GameWorld.h"
        "src/include/Snakey.h"
)

#### specific for Windows build (tested on: MS Visual Studio 2015)###
set_property(TARGET sdl2 PROPERTY IMPORTED_LOCATION "${SDL2_LIB_DIR}/lib/x86/SDL2.lib")
set_property(TARGET sdl2main PROPERTY IMPORTED_LOCATION "${SDL2_LIB_DIR}/lib/x86/SDL2main.lib")
#####################################################################


target_link_libraries(Snakey sdl2 sdl2main)

#install(TARGETS Snakey sdl2 sdl2main
        #RUNTIME DESTINATION ${CMAKE_CURRENT_LIST_DIR}/bin
        #LIBRARY DESTINATION ${CMAKE_CURRENT_LIST_DIR}/lib)
