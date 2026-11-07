CC = cc
CFLAGS = -Wall -Wextra -std=c11
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


TARGET = pong
OBJECTS = main.o GameUpdate.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) -g

main.o: main.c GameUpdate.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< -g

GameUpdate.o: GameUpdate.c GameUpdate.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< -g

clean:
	rm -f $(TARGET) $(OBJECTS)
