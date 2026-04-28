CXX = g++
CXXFLAGS = -std=c++14 -pthread -Wall

TARGET = snake_game
SRCS = main.cpp logic.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) hs_*.txt
