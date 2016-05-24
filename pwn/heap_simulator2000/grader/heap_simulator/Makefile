CFLAGS= -m32 -Wunused
LDFLAGS= -m32
CC=gcc
JEMALLOC_CFLAGS= -I./jemalloc-4.0.4/include/ -L./jemalloc-4.0.4/lib/ -Wl,-rpath,./jemalloc-4.0.4/lib/ -ljemalloc


alloc = alloc.o

objects = $(patsubst %.c,%.o,$(wildcard *.c))

all: simulator2000 simulator2001 simulator2002

real: CFLAGS += -DREAL_FLAG -lseccomp
real: all

$(objects): %.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

simulator2000: alloc.o heap_simulator2000.o
	$(CC) $^ -o $@ $(CFLAGS)

simulator2001: alloc.o heap_simulator2001.o
	$(CC) $^ -o $@ $(CFLAGS)

simulator2002: alloc.o heap_simulator2002.o
	$(CC) $^ -o $@ $(CFLAGS)

jemalloc1: CFLAGS += $(JEMALLOC_CFLAGS)
jemalloc1: jemalloc1.o
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm *.o
	rm simulator2000
	rm simulator2001
	rm simulator2002
