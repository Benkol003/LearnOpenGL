#checkout https://github.com/ttroy50/cmake-examples

cmake_minimum_required(VERSION 3.24)

project(OpenGL-Playground C CXX) #C needed for GLAD

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/lib/)
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/lib/)

find_package(OpenGL REQUIRED)

### GLFW ###
#disable unneccesary GLFW CMake stuff
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glfw)


### GLAD ###
set(GLAD_SOURCES_DIR ${CMAKE_SOURCE_DIR}/lib/glad/)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glad/cmake glad_cmake)
glad_add_library(glad_gl_core_33 STATIC API gl:core=3.3)

### GLM ###
find_package(glm CONFIG REQUIRED)

set(INCLUDES
PUBLIC
${CMAKE_SOURCE_DIR}/lib/stb/
${GLM_INCLUDE_DIR}
)

include_directories(${INCLUDES})


### Target main ####

set(SOURCES
${CMAKE_SOURCE_DIR}/src/main.cpp
${CMAKE_SOURCE_DIR}/src/icosphere.cpp
)

add_executable(main ${SOURCES})

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)

set(LIBS
PRIVATE
glfw
glad_gl_core_33
OpenGL::GL
glm::glm
)

target_link_libraries(main PUBLIC ${LIBS})

### copy resources alognside executable

add_custom_command(
  TARGET main POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources/
    $<TARGET_FILE_DIR:main>)


######




### cubes ###

add_executable(cubes ${CMAKE_SOURCE_DIR}/src/cubes/main.cpp)
target_include_directories(cubes PRIVATE ${CMAKE_SOURCE_DIR}/src/cubes/)
target_link_libraries(cubes PUBLIC ${LIBS})




