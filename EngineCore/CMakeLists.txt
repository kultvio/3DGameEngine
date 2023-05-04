cmake_minimum_required(VERSION 3.26)

set(ENGINE_PROJECT_NAME EngineCore)

add_library(${ENGINE_PROJECT_NAME} STATIC
	src/window.cpp
	src/window.h
	src/event.h
	src/keyEvent.h
	src/mouseEvent.h
	src/windowEvent.h
	src/application.h
	src/application.cpp
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(depend/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC glfw)

add_subdirectory(depend/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC glad)