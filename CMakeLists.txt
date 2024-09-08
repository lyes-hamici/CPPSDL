#=================================
# Base Options
#=================================
cmake_minimum_required(VERSION 3.16)
project(2048 LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Build)
set(useSDL 0)
set(useSFML 0)
set(languageStandard 23)
#=================================
# Setup
#=================================
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
cmake_policy(SET CMP0115 NEW)
#=================================
# Executable
#=================================
add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/Core/main.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_${languageStandard})
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/Core
	${CMAKE_SOURCE_DIR}/src/Game
	${CMAKE_SOURCE_DIR}/src/Input
	${CMAKE_SOURCE_DIR}/src/Renderer
)
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp *.hpp)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
#=================================
# SDL
#=================================
if(useSDL)
	target_link_libraries(${PROJECT_NAME}
		PRIVATE PRIVATE SDL2main
		PRIVATE PRIVATE SDL2
		PRIVATE PRIVATE SDL2_image
		#PRIVATE PRIVATE SDL2_ttf
	)
endif()
#=================================
# SFML
#=================================
if(useSFML)
	include(FetchContent)
	FetchContent_Declare(SFML
		GIT_REPOSITORY https://github.com/SFML/SFML.git
		GIT_TAG 2.6.x
	)
	FetchContent_MakeAvailable(SFML)
	target_link_libraries(${PROJECT_NAME}
		PRIVATE sfml-graphics
		PRIVATE sfml-window
	)
endif()
#=================================
# Pre-process
#=================================
install(TARGETS ${PROJECT_NAME})