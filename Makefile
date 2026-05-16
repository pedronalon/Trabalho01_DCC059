
CXX = g++
CXXFLAGS = -std=c++20 -Wall


TARGET_NAME = Trabalho01_DCC059

$(OBJS): Grafo.hpp
SRCS = main.cpp grafo.cpp
OBJS = $(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
    TARGET = $(TARGET_NAME).exe
    RM_CMD = del /Q /F *.o $(TARGET_NAME).exe
    RUN_CMD = $(TARGET)
else
    
    TARGET = $(TARGET_NAME)
    
    RM_CMD = rm -f $(OBJS) $(TARGET)
    
    RUN_CMD = ./$(TARGET)
endif


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	$(RM_CMD)

run: $(TARGET)
	$(RUN_CMD)