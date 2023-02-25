####################################################
# Generic makefile
# for compiling and linking C++ projects on Linux 
# Author: George Foot  Modified:Jackie Lee
####################################################
### Customising
#
# Adjust the following if necessary; EXECUTABLE is the target
# executable's filename, and LIBS is a list of libraries to link in
# (e.g. alleg, stdcx, iostr, etc). You can override these on make's
# command line of course, if you prefer to do it that way.
#
EXECUTABLE := simple-vim
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
#
# Now alter any implicit rules' variables if you like, e.g.:
#
CC := g++
CFLAGS := -g -Wall -std=c++14 -O3
CPPFLAGS := $(CFLAGS)
#
# The next bit checks to see whether rm is in your djgpp bin
# directory; if not it uses del instead, but this can cause (harmless)
# `File not found' error messages. If you are not using DOS at all,
# set the variable to something which will unquestioningly remove
# files.
#
RM-F := rm -f
#
# You shouldn't need to change anything below this point.
#
SRCS := $(wildcard $(addsuffix /*.cpp, $(SRC_DIR)))
OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(patsubst $(SRC_DIR)/%, %, $(SRCS)))

.PHONY : all clean veryclean rebuild info

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/Editor.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/InsertTxt.o: $(SRC_DIR)/InsertTxt.cpp $(INCLUDE_DIR)/InsertTxt.h $(INCLUDE_DIR)/NormalTxt.h $(INCLUDE_DIR)/EditorScreen.h $(INCLUDE_DIR)/Txt.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/NormalTxt.o: $(SRC_DIR)/NormalTxt.cpp $(INCLUDE_DIR)/NormalTxt.h $(INCLUDE_DIR)/InsertTxt.h $(INCLUDE_DIR)/EditorScreen.h $(INCLUDE_DIR)/GoodbyeScreen.h $(INCLUDE_DIR)/Editor.h $(INCLUDE_DIR)/Txt.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/Txt.o: $(SRC_DIR)/Txt.cpp $(INCLUDE_DIR)/Txt.h $(INCLUDE_DIR)/CursorOp.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/Editor.o: $(SRC_DIR)/Editor.cpp $(INCLUDE_DIR)/Editor.h $(INCLUDE_DIR)/WelcomeScreen.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/GoodbyeScreen.o: $(SRC_DIR)/GoodbyeScreen.cpp $(INCLUDE_DIR)/Screen.h $(INCLUDE_DIR)/CursorOp.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/EditorScreen.o: $(SRC_DIR)/EditorScreen.cpp $(INCLUDE_DIR)/Screen.h $(INCLUDE_DIR)/Txt.h $(INCLUDE_DIR)/NormalTxt.h $(INCLUDE_DIR)/WelcomeScreen.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/WelcomeScreen.o: $(SRC_DIR)/WelcomeScreen.cpp $(INCLUDE_DIR)/WelcomeScreen.h $(INCLUDE_DIR)/Screen.h $(INCLUDE_DIR)/CursorOp.h $(INCLUDE_DIR)/EditorScreen.h $(INCLUDE_DIR)/Editor.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/Screen.o: $(SRC_DIR)/Screen.cpp $(INCLUDE_DIR)/Screen.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BUILD_DIR)/CursorOp.o: $(SRC_DIR)/CursorOp.cpp $(INCLUDE_DIR)/CursorOp.h
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@$(RM-F) $(BUILD_DIR)/*.o

veryclean: clean
	@$(RM-F) $(EXECUTABLE)

rebuild: veryclean all
	
info:
	@echo "srcs:" $(SRCS)
	@echo "objs:" $(OBJS)
