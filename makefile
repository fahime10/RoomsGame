CXX      = g++
CXXFLAGS = -O0 -g3 -std=c++17

SOURCES  = $(wildcard *.cpp)

OBJECTS  = $(patsubst %.cpp, %.o, $(filter %.cpp, $(SOURCES)))

TARGET   = main

all: $(TARGET)	

$(TARGET): $(OBJECTS)
	@echo "Linking $@"
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	@echo "Compiling $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)
