CC = gcc
CFLAGS = -c -g -Wall

SOURCES = traitement_image.c

OBJS = $(SOURCES:%.c=%.o)

INCLUDES = `pkg-config sdl2 --cflags` `pkg-config SDL2_image --cflags`

all : libtraitement_image.a

libtraitement_image.a : $(OBJS)
	ar crU $@ $^
	ranlib $@

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

traitement_image.o : traitement_image.h ../my_struct_images/my_struct_images.h ../traitement_fenetre/traitement_fenetre.h  

clean :
	rm -f libtraitement_image.a $(OBJS)