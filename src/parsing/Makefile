CC = gcc
CFLAGS = -c -g -Wall

SOURCES = parsing.c

OBJS = $(SOURCES:%.c=%.o)

INCLUDES =`pkg-config sdl2 --cflags` `pkg-config SDL2_image --cflags`

all : libparsing.a

libparsing.a : $(OBJS)
	ar cru $@ $^
	ranlib $@

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

parsing.o : ../gestions/my_struct_images/my_struct_images.h ../gestions/traitement_image/traitement_image.h  parsing.h

clean :
	rm -f libparsing.a $(OBJS)