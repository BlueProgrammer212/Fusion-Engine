cmake_minimum_required(VERSION 3.5)

project(FusionGameEngine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLFW")
set(GLEW_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW")
set(GLM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm")
set(STBI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stbi")
set(IRRKLANG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/irrKlang/irrKlang")
set(ASSIMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp")

set(ZLIB_INCLUDE_DIRS ${ASSIMP_DIR}/contrib/zlib/contrib)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/include/imgui
                    ${GLFW_DIR}/include
                    ${GLEW_DIR}/include
                    ${STBI_DIR}
                    ${GLM_DIR}
                    ${ASSIMP_DIR}/include
                    ${IRRKLANG_DIR}/include)

set(GLFW_LIBRARY_DIR ${GLFW_DIR}/lib-vc2022)
set(GLEW_LIBRARY_DIR ${GLEW_DIR}/lib)
set(IRRKLANG_LIBRARY_DIR ${IRRKLANG_DIR}/lib)
set(ASSIMP_LIBRARY_DIR ${ASSIMP_DIR}/lib/Debug)

set(GLFW_LIBRARIES
    ${GLFW_LIBRARY_DIR}/glfw3.lib
)

set(GLEW_LIBRARIES
    ${GLEW_LIBRARY_DIR}/glew32s.lib
)

set(IRRKLANG_LIBRARIES
    ${IRRKLANG_LIBRARY_DIR}/Winx64-visualStudio/irrKlang.lib)

set(ASSIMP_LIBRARIES
    ${ASSIMP_LIBRARY_DIR}/assimp-vc143-mtd.lib)

set(ZLIB_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp/contrib/zlib/Debug/zlibstaticd.lib)

file (GLOB SOURCES "src/*.cpp")
file (GLOB IMGUI_SOURCES "src/imgui/*.cpp")

add_executable(My3dGame ${SOURCES} ${IMGUI_SOURCES} ${HEADERS})

target_link_libraries(My3dGame 
                      ${GLFW_LIBRARIES}
                      ${GLEW_LIBRARIES}
                      ${IRRKLANG_LIBRARIES}
                      ${ASSIMP_LIBRARIES}
                      ${ZLIB_LIBRARIES}
                      opengl32.lib)

set_target_properties(My3dGame PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)