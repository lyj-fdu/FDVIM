CC       := @g++
CPPFLAGS := -g -Wall -std=c++14 -O3
RM       := @del

EXECUTABLE := fdvim.exe
SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(SRCS))

.PHONY : clean veryclean info

$(EXECUTABLE): $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS)

clean:
	$(RM) $(OBJS)

veryclean: clean
	$(RM) $(EXECUTABLE)

info:
	@echo "exe:"  $(EXECUTABLE)
	@echo "srcs:" $(SRCS)
	@echo "objs:" $(OBJS)
