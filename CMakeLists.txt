cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME GameEngine)

add_subdirectory(EngineCore)
add_subdirectory(EngineEditor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT EngineEditor)