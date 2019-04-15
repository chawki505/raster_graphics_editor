CC = gcc
CFLAGS = -g -Wall

NAME = graphics_test

SOURCES = main.c

OBJS = $(SOURCES:%.c=%.o)


all :
	make $(NAME)
	make clean

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) -c $(CFLAGS) $<

main.o : common.h

clean :
	rm -f $(OBJS)

fullclean :
	make clean
	rm -f $(NAME) $(OBJS)
