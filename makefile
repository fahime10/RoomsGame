CXX      = g++
CXXFLAGS = -O0 -g3 -std=c++17 -I./classes

SRCDIR 	 = ./classes

SOURCES  = $(wildcard $(SRCDIR)/*.cpp) main.cpp GameFlow.cpp

OBJECTS  = $(patsubst %.cpp, %.o, $(filter %.cpp, $(SOURCES)))

TARGET   = main

all: $(TARGET)

# main: main.cpp
# 	g++ main.cpp -o main
	

$(TARGET): $(OBJECTS)
	@echo "Linking $@"
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)
