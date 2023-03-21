#Files that will be compiled
SRC_DIR = game/src
OBJS = $(SRC_DIR)/stb.cpp $(SRC_DIR)/shader.cpp $(SRC_DIR)/texture.cpp $(SRC_DIR)/bullet.cpp $(SRC_DIR)/enemy.cpp $(SRC_DIR)/gun.cpp $(SRC_DIR)/square.cpp $(SRC_DIR)/mothership.cpp $(SRC_DIR)/player.cpp $(SRC_DIR)/main.cpp $(SRC_DIR)/glad.c

#OBJS += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
#OBJS += $(IMGUI_DIR)/imgui_impl_glfw.cpp $(IMGUI_DIR)/imgui_impl_opengl3.cpp
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
