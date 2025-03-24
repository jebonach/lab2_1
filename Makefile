CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = lab1
OBJ = main.o interface.o matrix.o fieldinfo.o real.o complex.o errors.o

all: $(TARGET)
	clear
	./$(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c interface.h matrix.h real.h complex.h
	$(CC) $(CFLAGS) -c main.c

interface.o: interface.c interface.h matrix.h errors.h
	$(CC) $(CFLAGS) -c interface.c

matrix.o: matrix.c matrix.h errors.h
	$(CC) $(CFLAGS) -c matrix.c

fieldinfo.o: fieldinfo.c fieldinfo.h
	$(CC) $(CFLAGS) -c fieldinfo.c

real.o: real.c real.h fieldinfo.h
	$(CC) $(CFLAGS) -c real.c

complex.o: complex.c complex.h fieldinfo.h
	$(CC) $(CFLAGS) -c complex.c

errors.o: errors.c errors.h
	$(CC) $(CFLAGS) -c errors.c

clean:
	rm -f *.o $(TARGET)
