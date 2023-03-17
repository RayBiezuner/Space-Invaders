#Files that will be compiled
IMGUI_DIR = imgui
OBJS = stb.cpp shader.cpp texture.cpp bullet.cpp enemy.cpp gun.cpp square.cpp mothership.cpp player.cpp main.cpp glad.c
OBJS += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
OBJS += $(IMGUI_DIR)/imgui_impl_glfw.cpp $(IMGUI_DIR)/imgui_impl_opengl3.cpp
#Used compiler
CC = g++

#Path to aditional files needed to compile
INCLUDE_PATHS = -Iinclude

#Path to libraries needed to compile
LIBRARY_PATHS = -Llibs

#Aditional compile options
COMPILER_FLAGS = 

#Specifies which libraries we're linking
LINKER_FLAGS = -lGL -lglfw

#Executable name
EXE_NAME = demo

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE_NAME)
