project(${EXECUTABLE_NAME})
message(STATUS "${CMAKE_PROJECT_NAME}: Building executable...")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

#removing precompiled headers from the source list
list(REMOVE_ITEM MY_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/mbtpch.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mbtpch.h"
)

add_executable(${EXECUTABLE_NAME})

set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 23)
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_EXTENSIONS OFF)

target_sources(${EXECUTABLE_NAME} PRIVATE ${MY_SOURCES} )

target_precompile_headers(${EXECUTABLE_NAME} PRIVATE "mbtpch.h")

target_compile_definitions(${EXECUTABLE_NAME} PRIVATE ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

if(MSVC)
	target_compile_definitions(${EXECUTABLE_NAME} PRIVATE -D_CRT_SECURE_NO_WARNINGS)

	#remove console
	#set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

target_include_directories(${EXECUTABLE_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/")

target_link_libraries(${EXECUTABLE_NAME} PRIVATE mabble glfw imgui glm spdlog )