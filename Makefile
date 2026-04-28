# Compiler
CXX = g++
# Compiler flags (adding -pthread for threading support)
CXXFLAGS = -std=c++11 -pthread -Wall

# Target executable name
TARGET = snake_game

# Source files
SRCS = main.cpp logic.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) highscores.txt
