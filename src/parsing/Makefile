CC = gcc
CFLAGS = -c -g -Wall

SOURCES = parsing.c

OBJS = $(SOURCES:%.c=%.o)

INCLUDES = -I ../ `pkg-config sdl2 --cflags` `pkg-config SDL2_image --cflags`

all : libparsing.a

libparsing.a : $(OBJS)
	ar crU $@ $^
	ranlib $@

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

parsing.o : parsing.h ../gestions/traitement_image/traitement_image.h

clean :
	rm -f libparsing.a $(OBJS)