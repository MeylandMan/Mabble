cmake_minimum_required(VERSION 3.16...4.0 FATAL_ERROR)
project(Mabble VERSION 0.0.0 LANGUAGES CXX)

include(cmake/thirdparty.cmake)

# tests subdirectories
add_subdirectory(${INCLUDE_DIR_GLFW})
add_subdirectory(${INCLUDE_DIR_ASSIMP})
add_subdirectory(${INCLUDE_DIR_GLM})
add_subdirectory(${INCLUDE_DIR_IMGUI})
add_subdirectory(${INCLUDE_DIR_SPDLOG})


add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/stb_image)
add_subdirectory(thirdparty/msdf-atlas-gen)
add_subdirectory(tests)


file(GLOB_RECURSE MB_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
set(MB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library("${CMAKE_PROJECT_NAME}")

# Visual Studio
if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()


target_compile_definitions("${CMAKE_PROJECT_NAME}" PRIVATE
    "$<$<CONFIG:Debug>:MB_DEBUG>"
    "$<$<CONFIG:Release>:MB_RELEASE>"
)

target_compile_options("${CMAKE_PROJECT_NAME}" PRIVATE
    "$<$<CONFIG:Debug>:/MDd>"
    "$<$<CONFIG:Release>:/MD>"
)

# Activating debug an optimization
set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES
    COMPILE_PDB_NAME_DEBUG "Mabble_Debug"
    COMPILE_PDB_NAME_RELEASE "Mabble_Release"
)

option(MB_NO_PCH "Desactivate precompiled headers" OFF)
if(NOT MB_NO_PCH)
    target_precompile_headers("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/mbpch.h")
endif()

target_sources("${CMAKE_PROJECT_NAME}" PUBLIC ${MB_SOURCES})
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC ${MB_HEADERS})

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE
	glad
	stb_image
    "$<$<CONFIG:Debug>:${THIRD_LIBRARY_SHADERCD}"
    "$<$<CONFIG:Debug>:${THIRD_LIBRARY_SPRIV_CROSSD}"
    "$<$<CONFIG:Debug>:${THIRD_LIBRARY_SPRIV_CROSS_GLSLD}"

	"$<$<CONFIG:Release>:${THIRD_LIBRARY_SHADERC}"
    "$<$<CONFIG:Release>:${THIRD_LIBRARY_SPRIV_CROSS}"
    "$<$<CONFIG:Release>:${THIRD_LIBRARY_SPRIV_CROSS_GLSL}"
)