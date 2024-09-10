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
	target_compile_definitions(${PROJECT_NAME} PUBLIC USE_SDL=${USE_SDL})
	include(FetchContent)
	FetchContent_Declare(
		SDL2
		GIT_REPOSITORY https://github.com/libsdl-org/SDL
		GIT_TAG 9519b9916cd29a14587af0507292f2bd31dd5752
		GIT_PROGRESS TRUE
	)
	# sdl2_image
	FetchContent_Declare(
		SDL2_IMAGE
		GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
		GIT_TAG abcf63aa71b4e3ac32120fa9870a6500ddcdcc89
		GIT_PROGRESS TRUE
		)
		# # # harfbuzz
		# FetchContent_Declare(
		# 	HARFBUZZ
		# 	GIT_REPOSITORY https://github.com/harfbuzz/harfbuzz.git
		# 	GIT_TAG 9c03576c49db6e7207d9bcdfe3abd170a809157f
		# 	GIT_PROGRESS TRUE
		# 	)
		# # freetype
		# FetchContent_Declare(
		# 	FREETYPE
		# 	GIT_REPOSITORY https://github.com/freetype/freetype
		# 	GIT_TAG 42608f77f20749dd6ddc9e0536788eaad70ea4b5
		# 	GIT_PROGRESS TRUE
		# 	)
	# sdl2_ttf
	# FetchContent_Declare(
	# 	SDL2_TTF
	# 	GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
	# 	GIT_TAG 4a318f8dfaa1bb6f10e0c5e54052e25d3c7f3440
	# 	GIT_PROGRESS TRUE
	# 	)
	# FetchContent_GetProperties(freetype)
	FetchContent_MakeAvailable(SDL2 SDL2_IMAGE)
	target_link_libraries(${PROJECT_NAME}
		 PRIVATE SDL2main
		#  PRIVATE SDL2::SDL2
		PRIVATE SDL2-static
		 PRIVATE SDL2_image
		#  PRIVATE SDL2_ttf
	)
endif()
#=================================
# SFML
#=================================
if(USE_SFML)
	target_compile_definitions(${PROJECT_NAME} PUBLIC USE_SFML=${USE_SFML})
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
# WindowsConsole
#=================================
if(USE_WINDOWSCONSOLE)
	target_compile_definitions(${PROJECT_NAME} PUBLIC USE_WINDOWSCONSOLE=${USE_WINDOWSCONSOLE})
endif()
#=================================
# Pre-process
#=================================
install(TARGETS ${PROJECT_NAME})