CC = cc
CFLAGS = -Wall -Wextra -std=c11
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11


TARGET = pong
OBJECTS = main.o InputController.o Player.o ClientSideUpdate.o Actions.o

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) -g

main.o: main.c ClientSideUpdate.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< -g

Player.o: Player.c Player.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< -g

InputController.o: InputController.c InputController.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< -g

ClientSideUpdate.o: ClientSideUpdate.c Actions.c ClientSideUpdate.h Player.h GameInitConstants.h Actions.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< -g

Actions.o: Actions.c Actions.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< -g
 
clean:
	rm -f $(TARGET) $(OBJECTS)
