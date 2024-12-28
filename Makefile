NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = pipex.c utils.c 
OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
$(LIBFT):
	make -C libft 
clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
	make fclean -C libft

re : fclean all 
	
