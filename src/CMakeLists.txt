
add_library(mabble ${MABBLE_LIBRARY_TYPE} 
                   "${CMAKE_SOURCE_DIR}/include/mabble/mabble.h")
message(STATUS "${CMAKE_PROJECT_NAME}: Building library...")

target_compile_definitions(mabble PRIVATE
    $<$<CONFIG:Debug>:MABBLE_DEBUG>
    $<$<CONFIG:Release>:MABBLE_RELEASE>
    MABBLE_BUILD
)

target_compile_definitions(mabble PUBLIC
    MABBLE_VERSION="${MABBLE_FULL_VERSION}"
)

# Activating debug an optimization
set_target_properties(mabble PROPERTIES
    COMPILE_PDB_NAME_DEBUG "Mabble_Debug"
    COMPILE_PDB_NAME_RELEASE "Mabble_Release"
)

file(GLOB_RECURSE MB_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(mabble PRIVATE ${MB_SOURCES})
target_include_directories(mabble PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/")

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
