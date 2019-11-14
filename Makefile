CC = gcc
CFLAGS = 
OBJECT = smallsh.o command.o  check.o
TARGET = smallsh

$(TARGET) : $(OBJECT)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECT)

smallsh.o : smallsh.h smallsh.c
	$(CC) $(CFLAGS) -c -o smallsh.o smallsh.c

command.o : command.c
	$(CC) $(CFLAGS) -c -o command.o command.c

check.o : check.c
	$(CC) $(CFLAGS) -c -o check.o check.c


clean :
	rm -f *.o
	rm -f $(TARGET)
