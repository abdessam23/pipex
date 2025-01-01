NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = pipex.c utils.c ft_split.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c \
      ft_putstr_fd.c \
      ft_substr.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all 

.PHONY: clean fclean all re 
