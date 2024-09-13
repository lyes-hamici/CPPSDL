#=================================
# Base Options
#=================================
cmake_minimum_required(VERSION 3.16)
project(2048 LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Build)
set(USE_SDL 1)
set(USE_SFML 0)
set(USE_WINDOWSCONSOLE 0)
set(languageStandard 23)
#=================================
# Setup
#=================================
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
cmake_policy(SET CMP0115 NEW)
#=================================
# Executable
#=================================
add_executable(${PROJECT_NAME}
	${CMAKE_SOURCE_DIR}/src/Core/main.cpp
	${CMAKE_SOURCE_DIR}/src/Game/Board.cpp
	${CMAKE_SOURCE_DIR}/src/Game/Game.cpp
	${CMAKE_SOURCE_DIR}/src/Game/File.cpp
	${CMAKE_SOURCE_DIR}/src/Input/Input.cpp
	${CMAKE_SOURCE_DIR}/src/Renderer/Renderer.cpp
)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_${languageStandard})
#=================================
# SDL
#=================================
if(USE_SDL)
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "2048 SDL2")
	target_compile_definitions(${PROJECT_NAME} PUBLIC USE_SDL=${USE_SDL})
	target_include_directories(${PROJECT_NAME} PUBLIC src/LibSDL)
	target_link_directories(${PROJECT_NAME} PUBLIC src/LibSDL/lib)
	target_link_libraries(${PROJECT_NAME}
		mingw32
		SDL2main
		SDL2
		SDL2_image
		SDL2_ttf
	)
endif()
#=================================
# SFML
#=================================
if(USE_SFML)
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "2048 SFML")
	target_compile_definitions(${PROJECT_NAME} PUBLIC USE_SFML=${USE_SFML})
	include(FetchContent)
	FetchContent_Declare(SFML
		GIT_REPOSITORY https://github.com/SFML/SFML.git
		GIT_TAG 2.6.x
	)
	FetchContent_MakeAvailable(SFML)
	target_link_libraries(${PROJECT_NAME}
		sfml-graphics
		sfml-window
	)
endif()
#=================================
# WindowsConsole
#=================================
if(USE_WINDOWSCONSOLE)
	set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "2048 WindowsConsole")
	target_compile_definitions(${PROJECT_NAME} PUBLIC USE_WINDOWSCONSOLE=${USE_WINDOWSCONSOLE})
endif()
#=================================
# Pre-process
#=================================
install(TARGETS ${PROJECT_NAME})

#=================================
# Test executable
#=================================
# Create a new executable for tests that only compiles test.cpp and Board.cpp
add_executable(testBattery
    ${CMAKE_SOURCE_DIR}/tests/test.cpp
    ${CMAKE_SOURCE_DIR}/src/Game/File.cpp
)

set_target_properties(testBattery PROPERTIES OUTPUT_NAME "2048 Test")

target_compile_features(testBattery PRIVATE cxx_std_${languageStandard})

#=================================
# Fetch GoogleTest for testBattery
#=================================
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(testBattery
    gtest
    gtest_main
)