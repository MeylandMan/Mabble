if(BUILD_SHARED_LIBS)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>")
else()
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(EXECUTABLE_NAME "prototype")

project(${EXECUTABLE_NAME})
message(STATUS "${CMAKE_PROJECT_NAME}: Building executable...")

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE MY_HEADERS CONFIGURE_DEPENDS 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)


add_executable(${EXECUTABLE_NAME})

set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD 23)
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${EXECUTABLE_NAME} PROPERTY CXX_EXTENSIONS OFF)

target_sources(${EXECUTABLE_NAME} PRIVATE ${MY_SOURCES} )

if(MSVC)

	target_compile_definitions(${EXECUTABLE_NAME} PUBLIC -D_CRT_SECURE_NO_WARNINGS)

	#remove console
	#set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
	
	if(BUILD_SHARED_LIBS)
		set_property(TARGET ${EXECUTABLE_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
	else()
		set_property(TARGET ${EXECUTABLE_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
	endif()

endif()

target_include_directories(${EXECUTABLE_NAME} PUBLIC ${MY_HEADERS})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE mabble glfw imgui glm spdlog )