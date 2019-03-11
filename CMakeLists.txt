cmake_minimum_required(VERSION 3.13)
project(opengl-teste)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(glfw3_DIR "${MINGW}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fpermissive -lopengl32 -lglu32 -lglfw3")
set(DCMAKE_SH "CMAKE_SH-NOTFOUND")

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
include_directories(${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC
                           ${OPENGL_INCLUDE_DIR} ${GLUT_INCLUDE_DIRS})

file(GLOB SOURCE_FILES
     *.c
     *.cpp
     *.h)

set_target_properties(opengl-teste PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARY} opengl32 glu32 glfw3)