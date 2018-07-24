CXXFLAGS= -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++11
LDFLAGS= -lncurses
EXECUTABLE=hlousja5
SOURCES=src/main.cpp src/game.cpp src/being.cpp src/ghost.cpp src/pacman.cpp src/Clyde.cpp src/Blinky.cpp src/Pinky.cpp src/Inky.cpp
 
all: $(SOURCES:.cpp=.o)
	$(CXX) $(SOURCES:.cpp=.o) $(LDFLAGS) -o $(EXECUTABLE)
 
compile: all

clean:
	rm -rf doc
	rm -rf $(SOURCES:.cpp=.o) $(EXECUTABLE) 

 
run:
	./$(EXECUTABLE)

doc:
	doxygen src/Doxyfile
