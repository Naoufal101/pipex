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
BFILES = $(BFILES:.c=.o)

all: $(NAME)
bonus: $(BTARGET)

$(LIBRARY):
	@make -C $(INC) all clean

$(NAME): $(LIBRARY) $(OFILES) $(HEADER)
	$(CC) $(OFILES) $(LIBRARY) -o $(NAME)

$(BTARGET): $(LIBRARY) $(BOFILES) $(BHEADER)
	$(CC) $(BOFILES) $(LIBRARY) -o $(BTARGET)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME) $(LIBRARY)

re: fclean all