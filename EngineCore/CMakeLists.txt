cmake_minimum_required(VERSION 3.26)

set(ENGINE_PROJECT_NAME EngineCore)

set(ENGINE_SRC
	src/window.cpp
	src/window.h
	src/camera.cpp
	src/camera.h
	src/event.h
	src/keyEvent.h
	src/mouseEvent.h
	src/windowEvent.h
	src/application.h
	src/application.cpp
	src/Rendering/ShaderProgram.cpp
	src/Rendering/ShaderProgram.h
	src/Rendering/VertexBuffer.cpp
	src/Rendering/VertexBuffer.h
	src/Rendering/VertexArray.cpp
	src/Rendering/VertexArray.h
	src/Rendering/IndexBuffer.cpp
	src/Rendering/IndexBuffer.h
)


add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_SRC}
)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${ENGINE_SRC}
)
target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC src)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(depend/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC glfw)

add_subdirectory(depend/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC glad)


add_subdirectory(depend/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glm)

set(IMGUI_INCLUDES
	depend/imgui/imgui.h
	depend/imgui/backends/imgui_impl_glfw.h
	depend/imgui/backends/imgui_impl_opengl3.h
)

set(IMGUI_SOURCES
	depend/imgui/imgui.cpp
	depend/imgui/backends/imgui_impl_glfw.cpp
	depend/imgui/backends/imgui_impl_opengl3.cpp
	depend/imgui/imgui_demo.cpp
	depend/imgui/imgui_draw.cpp
	depend/imgui/imgui_tables.cpp
	depend/imgui/imgui_widgets.cpp
)


add_library(ImGui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)
target_include_directories(ImGui PUBLIC depend)
target_include_directories(ImGui PUBLIC depend/imgui)
target_link_libraries(ImGui PUBLIC glad glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PUBLIC ImGui)