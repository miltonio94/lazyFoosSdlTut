##
# Project Title
#
# @file
# @version 0.1

# OBJS specifies which files to compile
OBJS=main.cpp

# CC specifies which compiler
CC=g++

# COMPILER_FLAGS additional compilation options
# -w is the flag to supress all warnings
COMPILER_FLAGS= -w

DEBUG_FLAGS= -g

# LINKER_FLAGS defines the libraries we will be using
LINKER_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# OBJS_BUILD_PATH location for build programs to be dumped
OBJS_BUILD_PATH=../build/

# OBJS_NAME specifies the name of the executable
OBJS_NAME=colourKeying

# target that compiles
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJS_BUILD_PATH)$(OBJS_NAME)

dev : $(OBJS)
	$(CC) $(OBJS) $(DEBUG_FLAGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJS_BUILD_PATH)$(OBJS_NAME)

run : $(OBJS_BUILD_PATH)$(OBJS_NAME)
	$(OBJS_BUILD_PATH)$(OBJS_NAME)
# end
