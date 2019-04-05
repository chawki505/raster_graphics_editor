CC = gcc
CFLAGS = -c -g -Wall

SOURCES = my_struct_images.c

OBJS = $(SOURCES:%.c=%.o)

INCLUDES =`pkg-config sdl2 --cflags` `pkg-config SDL2_image --cflags`

all : libmy_struct_images.a

libmy_struct_images.a : $(OBJS)
	ar crU $@ $^
	ranlib $@

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

my_struct_images.o : ../../includes.h my_struct_images.h

clean :
	rm -f libmy_struct_images.a $(OBJS)