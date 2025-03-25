CC = gcc
CFLAGS = -Wall -Wextra -std=c11

TARGET = I_need_otl
OBJ = main.o interface.o matrix.o fieldinfo.o real.o complex.o errors.o tests.o

all: $(TARGET)
	@clear
	@sl -a -e
	@cowsay "поставьте отл, ну пожалуйста"
	@./$(TARGET)
	@clear
	@cowsay "как по мне лаба заслужила отл"

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c tests.h interface.h
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

tests.o: tests.c tests.h errors.h matrix.h real.h
	$(CC) $(CFLAGS) -c tests.c

clean:
	rm -f *.o $(TARGET)
	@clear
