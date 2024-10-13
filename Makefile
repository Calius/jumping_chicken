# Name des Programms
TARGET = jumping_chicken

# Compiler und Flags
CXX = g++
CXXFLAGS = -Wall -g

# SDL2 und SDL2_image Libraries
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LDFLAGS = $(shell sdl2-config --libs) -lSDL2_image

# Quellcode-Datei
SRC = jumping_chicken.cpp

# Objekt-Dateien
OBJ = $(SRC:.cpp=.o)

# Regel zum Kompilieren
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(SDL2_LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c $< -o $@

# Regel zum Ausführen des Programms
run: $(TARGET)
	./$(TARGET)

# Regel zum Bereinigen
clean:
	rm -f $(OBJ) $(TARGET)
