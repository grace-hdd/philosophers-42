NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCDIR = src
INCDIR = ./inc
SRCS_FILES = main_bonus.c \
             parsing_bonus.c \
             init_bonus.c \
             cleanup_bonus.c \
             utils_bonus.c \
             monitor_bonus.c \
             routine_bonus.c
SRCS = $(addprefix $(SRCDIR)/, $(SRCS_FILES))
OBJS = $(SRCS:.c=.o)
RM = rm -f

.PHONY: all bonus clean fclean re

all: bonus

bonus: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean bonus