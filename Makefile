CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = lab1
OBJ = main.o matrix.o real.o complex.o fieldinfo.o

all: $(TARGET)
	clear
	./$(TARGET)

$(TARGET): $(OBJ)
	clear
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c matrix.h real.h complex.h
	$(CC) $(CFLAGS) -c main.c

matrix.o: matrix.c matrix.h fieldinfo.h
	$(CC) $(CFLAGS) -c matrix.c

real.o: real.c real.h fieldinfo.h
	$(CC) $(CFLAGS) -c real.c

complex.o: complex.c complex.h fieldinfo.h
	$(CC) $(CFLAGS) -c complex.c

fieldinfo.o: fieldinfo.c fieldinfo.h
	$(CC) $(CFLAGS) -c fieldinfo.c

clean:
	clear
	rm -f *.o $(TARGET)
