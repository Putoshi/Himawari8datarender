# Makefile for st_render5_cpp
CC = g++
CFLAGS = -Wall -O2 -std=c++11
LDFLAGS = -lnetcdf -lurlmon

# Source files
SOURCES = main.cpp st_render.cpp colorscale.cpp lodepng.cpp others.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = st_render5_cpp

# Build target
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJECTS) $(TARGET)

# Dependencies
main.o: main.cpp st_render.h
st_render.o: st_render.cpp st_render.h lodepng.h
colorscale.o: colorscale.cpp st_render.h
lodepng.o: lodepng.cpp lodepng.h
others.o: others.cpp st_render.h