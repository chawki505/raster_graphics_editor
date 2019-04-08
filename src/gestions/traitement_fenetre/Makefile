CC = gcc
CFLAGS = -c -g -Wall

SOURCES = traitement_fenetre.c

OBJS = $(SOURCES:%.c=%.o)

INCLUDES =  `pkg-config sdl2 --cflags` `pkg-config SDL2_image --cflags`

all : libtraitement_fenetre.a

libtraitement_fenetre.a : $(OBJS)
	ar crU $@ $^
	ranlib $@

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) $<

traitement_fenetre.o : ../../includes.h traitement_fenetre.h 

clean :
	rm -f libtraitement_fenetre.a $(OBJS)