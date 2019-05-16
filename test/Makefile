CC = gcc
CFLAGS = -g -Wall

NAME = graphics_test

SOURCES = main.c testes.c

OBJS = $(SOURCES:%.c=%.o)

INCLUDES = `pkg-config sdl2 --cflags` `pkg-config SDL2_image --cflags`
LIBS = `pkg-config sdl2 --libs` `pkg-config SDL2_image --libs` -lreadline

PARSINGLIB = ../src/parsing/libparsing.a
MYSTRUCTIMAGESLIB = ../src/gestions/my_struct_images/libmy_struct_images.a
TRAITEMENTFENETRELIB = ../src/gestions/traitement_fenetre/libtraitement_fenetre.a
TRAITEMENTIMAGELIB = ../src/gestions/traitement_image/libtraitement_image.a



all :
	make test -C ../src
	make $(NAME)
	make clean

$(NAME) : $(OBJS) $(PARSINGLIB) $(TRAITEMENTIMAGELIB) $(TRAITEMENTFENETRELIB) $(MYSTRUCTIMAGESLIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $< $(INCLUDES)

testes.o : testes.h

clean :
	rm -f $(OBJS)

fullclean :
	make clean
	rm -f $(NAME) $(OBJS)
