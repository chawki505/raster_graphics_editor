CC = gcc
CFLAGS = -g -Wall -c

SOURCES = traitement_image.c

OBJS = $(SOURCES:%.c=%.o)

INCLUDES = `pkg-config sdl2 --cflags` `pkg-config SDL2_image --cflags`

all : libtraitement_image.a

libtraitement_image.a : $(OBJS)
	ar cru $@ $^
	ranlib $@

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

traitement_image.o : ../../includes.h ../my_struct_images/my_struct_images.h ../traitement_fenetre/traitement_fenetre.h  traitement_image.h

clean :
	rm -f libtraitement_image.a $(OBJS)