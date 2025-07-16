file(GLOB_RECURSE MB_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

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

target_sources(mabble PRIVATE ${MB_SOURCES} "core/temp.h")
target_include_directories(mabble PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/")

target_include_directories(mabble PUBLIC "${CMAKE_SOURCE_DIR}/include/")

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
