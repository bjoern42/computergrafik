CC      = /usr/bin/g++
CFLAGS  = -Wall -I../Utils 
LFLAGS	= -lGL -lGLU -lglut -L../Utils
#-Wall: prints "all" warning messages.
#-g: generates additional symbolic debuggging information for use with gdb debugger.

UTILS_SOURCES = $(wildcard ../Utils/*.cpp)
UTILS_OBJECTS = $(patsubst %.cpp, %.o, $(UTILS_SOURCES))

#SOURCES = Projection.cpp
#OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))
TARGET = Uebung3
TARGET_DIR = Debug/

all: $(TARGET)

$(TARGET): $(TARGET).o $(UTILS_OBJECTS) $(OBJECTS) 
	$(CC) $(CFLAGS) -o $(TARGET_DIR)$@ $^ $(LFLAGS)
	
$(TARGET).o : $(TARGET).cpp 
	$(CC) $(CFLAGS) -c $^ 
	
#$(OBJECTS): $(SOURCES)
#	$(CC) $(CFLAGS) -c $^
	
run: $(TARGET)
	./$(TARGET_DIR)$(TARGET)

.PHONY: all clean run
clean:
	rm $(UTILS_OBJECTS) $(TARGET).o $(TARGET_DIR)$(TARGET) $(OBJECTS)