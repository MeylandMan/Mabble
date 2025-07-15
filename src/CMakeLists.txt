file(GLOB_RECURSE MB_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
set(MB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(mabble ${MABBLE_LIBRARY_TYPE})
message(STATUS "${CMAKE_PROJECT_NAME}: Building library...")

target_compile_definitions(mabble PRIVATE
    "$<$<CONFIG:Debug>:MB_DEBUG>"
    "$<$<CONFIG:Release>:MB_RELEASE>"
)

target_compile_options(mabble PRIVATE
    "$<$<CONFIG:Debug>:/MDd>"
    "$<$<CONFIG:Release>:/MD>"
)

# Activating debug an optimization
set_target_properties(mabble PROPERTIES
    COMPILE_PDB_NAME_DEBUG "Mabble_Debug"
    COMPILE_PDB_NAME_RELEASE "Mabble_Release"
)

option(MB_NO_PCH "Desactivate precompiled headers" OFF)
if(NOT MB_NO_PCH)
    target_precompile_headers(mabble PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/mbpch.h")
endif()

target_sources(mabble PRIVATE ${MB_SOURCES})
target_include_directories(mabble PRIVATE ${MB_HEADERS})

target_link_libraries(mabble PRIVATE
	glad
	stb_image
    $<$<CONFIG:Debug>:${THIRD_LIBRARY_SHADERCD}>
    $<$<CONFIG:Debug>:${THIRD_LIBRARY_SPRIV_CROSSD}>
    $<$<CONFIG:Debug>:${THIRD_LIBRARY_SPRIV_CROSS_GLSLD}>

	$<$<CONFIG:Release>:${THIRD_LIBRARY_SHADERC}>
    $<$<CONFIG:Release>:${THIRD_LIBRARY_SPRIV_CROSS}>
    $<$<CONFIG:Release>:${THIRD_LIBRARY_SPRIV_CROSS_GLSL}>
)
