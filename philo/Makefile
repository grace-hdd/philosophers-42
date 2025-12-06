NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src
INCDIR = inc
SRCS = $(SRCDIR)/main.c $(SRCDIR)/parsing.c $(SRCDIR)/init.c $(SRCDIR)/cleanup.c $(SRCDIR)/utils.c $(SRCDIR)/monitor.c $(SRCDIR)/routine.c
OBJS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
