CXX = g++
CXXFLAGS = -Wall -g
LDFLAGS = -lGL -lGLU -lglut

TARGET = main

SRCDIR = src

OBJDIR = obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)

OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Create obj directory if it doesn't exist
$(shell mkdir -p $(OBJDIR))

# Rule to compile the executable
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Rule to compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean generated files
clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

# Default rule
.PHONY: clean
