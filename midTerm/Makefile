CC=g++
CFLAGS=-g -I../common/include -I../common/include/GL -I../common/include/SNDS -Iinclude -static-libgcc -static-libstdc++ -mwindows
LDFLAGS=-L../common/lib -lSOIL -lglut32 -lopengl32 -lglu32 -lwinmm -lirrKlang -lgdi32
SRC=$(wildcard src/*.cpp) main.cpp
OBJ=$(SRC:.cpp=.o)
EXEC=main.exe

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: all clean
