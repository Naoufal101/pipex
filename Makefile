FILES = Mandatory/pipex.c Mandatory/pipex_utils.c Mandatory/pipex_utils_I.c Mandatory/pipex_utils_II.c
BFILES = bonus/pipex_bonus.c bonus/pipex_utils_III_bonus.c bonus/pipex_utils_II_bonus.c \
		 bonus/pipex_utils_I_bonus.c bonus/pipex_utils_bonus.c bonus/gnl/get_next_line.c bonus/gnl/get_next_line_utils.c

NAME = pipex
INC = libft/
LIBRARY = libft.a
HEADER = Mandatory/pipex.h
BHEADER = bonus/pipex_bonus.h
BTARGET = pipex_bonus

CFLAGS = -Wall -Werror -Wextra
OFILES = $(FILES:.c=.o)
OBFILES = $(BFILES:.c=.o)

all: $(NAME)

$(LIBRARY):
	@make re -C $(INC)

$(NAME): $(LIBRARY) $(OFILES) $(HEADER)
	$(CC) $(CFLAGS) $(OFILES) $(LIBRARY) -o $(NAME)

bonus: $(LIBRARY) $(OBFILES) $(BHEADER)
	$(CC) $(CFLAGS) $(OBFILES) $(LIBRARY) -o $(NAME)

clean:
	$(RM) $(OFILES) $(OBFILES)

fclean: clean
	$(RM) $(NAME) $(LIBRARY) $(BTARGET)

re: fclean all