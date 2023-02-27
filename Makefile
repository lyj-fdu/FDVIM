CC := g++
CFLAGS := -g -Wall -std=c++14 -O3
CPPFLAGS := $(CFLAGS)
RM-F := rm -f

EXECUTABLE := simple-vim.exe
SRCS := $(wildcard src/*.cpp) $(wildcard main/*.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SRCS))

.PHONY : clean veryclean info

$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS)

clean:
	@$(RM-F) $(OBJS)

veryclean: clean
	@$(RM-F) $(EXECUTABLE)

info:
	@echo "exe:"  $(EXECUTABLE)
	@echo "srcs:" $(SRCS)
	@echo "objs:" $(OBJS)
