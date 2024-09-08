#==================================
# Setup
#==================================
compiler = g++
buildFlags = -std=c++23 -O3
buildPath = Build
cachePath = BuildCache
appName = 2048.exe
MakeDirectory = mkdir
#==================================
# Module Paths
#==================================
corePath = src/Core
gamePath = src/Game
inputPath = src/Input
inputWindowsConsolePath = src/Input/WindowsConsole
inputSDLPath = src/Input/SDL
inputSFMLPath = src/Input/SFML
rendererPath = src/Renderer
rendererWindowsConsolePath = src/Renderer/WindowsConsole
rendererSDLPath = src/Renderer/SDL
rendererSFMLPath = src/Renderer/SFML
libsPath =
#==================================
# App
#==================================
define AppCompile
	echo "Compile App: $<"
	$(compiler) $(buildFlags) -o $@ -c $< 
endef
$(cachePath)/%.o: $(corePath)/%.cpp
	$(AppCompile)
$(cachePath)/%.o: $(gamePath)/%.cpp
	$(AppCompile)
$(cachePath)/%.o: $(inputPath)/%.cpp
	$(AppCompile)
$(cachePath)/%.o: $(rendererPath)/%.cpp
	$(AppCompile)
#==================================
# SDL
#==================================
ifndef USE_SDL
	USE_SDL = 0
endif
ifeq ($(USE_SDL),1)
	SDLPath = src/LibSDL
	sdlFlags = -lSDL2main -lSDL2 -lSDL2_image
	libsPath += $(libsPath)/SDL
	buildFlags += $(sdlFlags)
	$(cachePath)/%.o: $(inputSDLPath)/%.cpp
		$(AppCompile)
	$(cachePath)/%.o: $(rendererSDLPath)/%.cpp
		$(AppCompile)
endif
#==================================
# SFML
#==================================
ifndef USE_SFML
	USE_SFML = 0
endif
ifeq ($(USE_SFML),1)
	SFMLPath = src/LibSFML
	SFMLFlags = -lsfml-graphics -lsfml-window
	libsPath += $(libsPath)/SFML
	buildFlags += $(sfmlFlags)
	$(cachePath)/%.o: $(inputSFMLPath)/%.cpp
		$(AppCompile)
	$(cachePath)/%.o: $(rendererSFMLPath)/%.cpp
		$(AppCompile)
endif
#==================================
# Windows Console
#==================================
ifndef USE_WINDOWSCONSOLE
	USE_WINDOWSCONSOLE = 0
endif
ifeq ($(USE_WINDOWSCONSOLE),1)
	$(cachePath)/%.o: $(inputWindowsConsolePath)/%.cpp
		$(AppCompile)
	$(cachePath)/%.o: $(rendererWindowsConsolePath)/%.cpp
		$(AppCompile)
endif
#==================================
# Build Pre-process
#==================================
ifneq ($(libsPath),)
	libsPath = -L $(libsPath)
endif
appObjects = $(wildcard $(cachePath)/*.o)
#==================================
# Rules
#==================================

SetupCache:
	$(MakeDirectory) $(cachePath)
Build:
	$(compiler) $(buildFlags) -o $(appName) $(appObjects) $(libsPath)
Clean:
	rm $(cachePath)/*
.PHONY: \
	SetupCache \
	Build \
	BuildApp \
	BuildSDL \
	BuildSFML \
	BuildWindowsConsole \
	Clean
