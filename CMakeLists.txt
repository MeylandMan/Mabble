cmake_minimum_required(VERSION 3.22...4.0 FATAL_ERROR)


project(Mabble VERSION 0.0.0 LANGUAGES CXX)
message(STATUS "Build Mabble: ${VERSION}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(MABBLE_BUILD_OPENGL "Build OpenGL mabble" ON)

include(cmake/build_library.cmake)
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