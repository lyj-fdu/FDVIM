CC := g++
CFLAGS := -g -Wall -std=c++14 -O3
CPPFLAGS := $(CFLAGS)
RM-F := rm -f

EXECUTABLE := simple-vim
INCLUDE_DIR := include
SRC_DIR := src
MAIN_DIR := main

SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(MAIN_DIR)/*.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SRCS))

.PHONY : clean veryclean info

$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS)

clean:
	@$(RM-F) $(OBJS)

veryclean: clean
	@$(RM-F) $(EXECUTABLE)

info:
	@echo "srcs:" $(SRCS)
	@echo "objs:" $(OBJS)
