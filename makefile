CC = gcc
CFLAGS = -fPIC -Wall -Wextra
LDFLAGS = -ldl -lm
TARGETS = libcontract1.so libcontract2.so static_program dynamic_program
OBJS = lib1.o lib2.o

.PHONY: all clean

all: $(TARGETS)

# Динамические библиотеки
libcontract1.so: lib1.o
	$(CC) -shared -o $@ $^ -lm

libcontract2.so: lib2.o
	$(CC) -shared -o $@ $^ -lm

# Объектные файлы
lib1.o: lib1.c contract.h
	$(CC) $(CFLAGS) -c lib1.c -o $@

lib2.o: lib2.c contract.h
	$(CC) $(CFLAGS) -c lib2.c -o $@

# Статическая программа
static_program: static_program.c libcontract1.so
	$(CC) -o $@ static_program.c -L. -lcontract1 -Wl,-rpath,. -lm

# Динамическая программа
dynamic_program: dynamic_program.c
	$(CC) -o $@ dynamic_program.c $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGETS)