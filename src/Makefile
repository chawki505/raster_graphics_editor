CC = gcc
CFLAGS = -g -Wall

NAME = graphics

SOURCES = main.c

OBJS = $(SOURCES:%.c=%.o)

INCLUDES = I . I parsing I gestions/my_struct_images I gestions/traitement_fenetre I gestions/traitement_image `pkg-config sdl2 --cflags` `pkg-config SDL2_image --cflags`

LIBS = `pkg-config sdl2 --libs` `pkg-config SDL2_image --libs` -lreadline

PARSINGLIB = parsing/libparsing.a
MYSTRUCTIMAGESLIB = gestions/my_struct_images/libmy_struct_images.a
TRAITEMENTFENETRELIB = gestions/traitement_fenetre/libtraitement_fenetre.a
TRAITEMENTIMAGELIB = gestions/traitement_image/libtraitement_image.a

all :
	make -C parsing
	make -C gestions
	make $(NAME)

$(NAME) : $(OBJS) $(PARSINGLIB) $(MYSTRUCTIMAGESLIB) $(TRAITEMENTFENETRELIB) $(TRAITEMENTIMAGELIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $<

main.o : includes.h parsing/parsing.h

clean :
	make -C parsing clean
	make -C gestions clean
	rm -f $(NAME) $(OBJS)