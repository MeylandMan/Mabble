cmake_minimum_required(VERSION 3.22...4.0 FATAL_ERROR)


project(Mabble VERSION 0.0.0 LANGUAGES CXX)
message(STATUS "Build Mabble: ${VERSION}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(MABBLE_BUILD_OPENGL "Build OpenGL mabble" ON)

#--------------------------------------------------------------------
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT ON CACHE BOOL "" FORCE)
#--------------------------------------------------------------------

set(MABBLE_LIBRARY_TYPE "${MABBLE_LIBRARY_TYPE}" CACHE STRING
    "Library type override for Mabble (SHARED, STATIC, OBJECT, or empty to follow BUILD_SHARED_LIBS)")

include(cmake/thirdparty.cmake)


#--------------------------------------------------------------------
# Add subdirectories
#--------------------------------------------------------------------

# tests subdirectories
add_subdirectory(${INCLUDE_DIR_GLFW})
add_subdirectory(${INCLUDE_DIR_ASSIMP})
add_subdirectory(${INCLUDE_DIR_GLM})
add_subdirectory(${INCLUDE_DIR_IMGUI})
add_subdirectory(${INCLUDE_DIR_SPDLOG})

# Mabble subdirectories
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/stb_image)
#add_subdirectory(thirdparty/msdf-atlas-gen)

# projects
add_subdirectory(src)
add_subdirectory(tests)