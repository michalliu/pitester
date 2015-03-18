TARGET = pitester
LIBS = -lpthread
CC = gcc
CFLAGS = -g -Wall

OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)

.PHONY: default all clean

default: $(TARGET)

all: default

install: all
	install -m 755 pitester  $(INSTALLPATH)/bin/

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f *.o
	-rm -f $(TARGET)	
