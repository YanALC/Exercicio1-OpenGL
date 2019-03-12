cmake_minimum_required(VERSION 3.13)
project(Exercicio1-OpenGL)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fpermissive -lopengl32 -lglu32")
set(DCMAKE_SH "CMAKE_SH-NOTFOUND")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(${PROJECT_NAME} main.cpp ImportadorBmp.cpp ImportadorBmp.h)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC
		${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

file(GLOB SOURCE_FILES
		*.c
		*.cpp
		*.h)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_gl_LIBRARY} opengl32 glu32)