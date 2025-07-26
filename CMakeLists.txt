cmake_minimum_required(VERSION 3.22...4.0 FATAL_ERROR)

include(cmake/version.cmake)


project(${MABBLE_PROJECT_NAME} VERSION ${MABBLE_VERSION} LANGUAGES CXX)
message(STATUS "Build Mabble: ${MABBLE_VERSION}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(EXECUTABLE_NAME "prototype")

string(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}" MABBLE_MAIN_BUILD)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(MABBLE_BUILD_OPENGL "Build OpenGL mabble" ON)



set(MABBLE_LIBRARY_TYPE "${MABBLE_LIBRARY_TYPE}" CACHE STRING
    "Library type override for Mabble (SHARED, STATIC, OBJECT, or empty to follow BUILD_SHARED_LIBS)")

if (MABBLE_LIBRARY_TYPE)
    if (MABBLE_LIBRARY_TYPE STREQUAL "SHARED")
        set(MABBLE_BUILD_SHARED_LIBRARY TRUE)
    else()
        set(MABBLE_BUILD_SHARED_LIBRARY FALSE)
    endif()
else()
    set(MABBLE_BUILD_SHARED_LIBRARY ${BUILD_SHARED_LIBS})
endif()

#--------------------------------------------------------------------
# Add subdirectories
#--------------------------------------------------------------------

include(cmake/thirdparty.cmake)

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

if(MABBLE_MAIN_BUILD)
    set_property(TARGET mabble PROPERTY FOLDER "Core")
    set_property(TARGET ${EXECUTABLE_NAME} PROPERTY FOLDER "Core")

    set_property(TARGET glfw PROPERTY FOLDER "Thirdparty")
    set_property(TARGET glad PROPERTY FOLDER "Thirdparty")
    set_property(TARGET glm PROPERTY FOLDER "Thirdparty")
    set_property(TARGET assimp PROPERTY FOLDER "Thirdparty")
    set_property(TARGET imgui PROPERTY FOLDER "Thirdparty")
    set_property(TARGET spdlog PROPERTY FOLDER "Thirdparty")
    set_property(TARGET stb_image PROPERTY FOLDER "Thirdparty")
endif()

