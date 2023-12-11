CXX      = g++
CXXFLAGS = -O0 -g3 -std=c++17

SOURCES  = $(wildcard *.cpp)

OBJECTS  = $(SOURCES:.cpp=.o)

TARGET   = main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)
