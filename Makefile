# Variablen für den Compiler und die Flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# SDL2 und SDL2_mixer Bibliotheken
SDL2_FLAGS = $(shell sdl2-config --cflags --libs) -lSDL2_image -lSDL2_mixer

# Zielname
TARGET = jumping_chicken

# Quellcode-Dateien
SRC = jumping_chicken.cpp

# Standard-Ziel
all: $(TARGET)

# Erzeuge die ausführbare Datei
$(TARGET):
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(SDL2_FLAGS)

# Bereinige die erzeugten Dateien
clean:
	rm -f $(TARGET)
