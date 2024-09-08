cmake_minimum_required(VERSION 3.16)
project(2048 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

cmake_policy(SET CMP0115 NEW)

add_executable(2048
    src/Core/*.cpp
    src/File/*.cpp
    src/Game/*.cpp
    src/Input/*.cpp
    src/Renderer/*.cpp
)

target_link_libraries(2048
    #SFML
    PRIVATE sfml-graphics
    #SDL2
	PRIVATE SDL2main
    PRIVATE SDL2
    PRIVATE SDL2_image
)

target_compile_features(2048 PRIVATE cxx_std_23)

install(TARGETS 2048)