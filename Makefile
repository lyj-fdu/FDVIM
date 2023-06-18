CC       := @g++
CPPFLAGS := -g -Wall -std=c++14 -O3
RM-F     := @rm -f

EXECUTABLE := fdvim.exe
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SRCS))

.PHONY : clean veryclean info

$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS)

clean:
	$(RM-F) $(OBJS)

veryclean: clean
	$(RM-F) $(EXECUTABLE)

info:
	@echo "exe:"  $(EXECUTABLE)
	@echo "srcs:" $(SRCS)
	@echo "objs:" $(OBJS)
