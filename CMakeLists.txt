cmake_minimum_required(VERSION 3.13)
project(opengl-teste)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -fpermissive")
set(CMAKE_CXX_FLAGS "-lopengl32 -lglu32")

find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})

file(GLOB SOURCE_FILES
		*.c
		*.cpp
		*.h
		)

add_executable(main.cpp ${SOURCE_FILES})

target_link_libraries (main.cpp ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} opengl32 glu32)