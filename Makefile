FILES = Mandatory/pipex.c Mandatory/pipex_utils.c Mandatory/pipex_utils_I.c Mandatory/pipex_utils_II.c

NAME = pipex
INC = libft/
LIBRARY = libft.a
HEADER = Mandatory/pipex.h

CFLAGS = -Wall -Werror -Wextra
OFILES = $(FILES:.c=.o)

all: $(NAME)

$(LIBRARY):
	@make -C $(INC) all clean

$(NAME): $(LIBRARY) $(OFILES) $(HEADER)
	$(CC) $(OFILES) $(LIBRARY) -o $(NAME)

clean:
	$(RM) $(OFILES)

fclean: clean
	$(RM) $(NAME) $(LIBRARY)

re: fclean all