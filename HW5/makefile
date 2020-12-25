#OBJ specifies which files compile as part of the project
OBJS = bagexam.cpp

#CC specifies which compiler we are using
CC = g++

#DEPS is the set of .h files the .cpp files depend on
DEPS = bag5.h bintree.h

#COMPILER FLAGS specifies the additional compilation options we can use
# -O2 is for recommended optimizations
# -Wall is for recommended compiler warnings
# -Wformat=2 is for additional checks
# march is to generate instructions for machine type (CPU). 
# march = native - CPU to generate code for at compilation time by determining the processor type of the compiling machine.

COMPILER_FLAGS = -O2 -Wall -Wformat=2 -march=native

#OBJ_NAME is the name of the executable
OBJ_NAME = bagexam

#This is the target that compiles everything together
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
