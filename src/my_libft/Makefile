NAME = mylibft.a
SOURCES = \
	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_printf.c ft_printunsnbr.c ft_printhexa.c \
	ft_putchar_fd.c ft_printpointer.c ft_printupphexa.c ft_printstr.c \
	ft_printnbr.c get_next_line_bonus.c ft_bufflen.c ft_buffjoin.c\
	ft_find.c ft_freemat.c ft_matlen.c ft_merge.c ft_strndup.c\
	ft_printf_fd.c ft_atoll.c ft_strcmp.c skip_spaces.c is_space.c is_quoted.c ft_matdup.c ft_strnncmp.c
BSOURCES = \
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJDIR = obj
OBJECTS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))
BOBJECTS = $(addprefix $(OBJDIR)/, $(BSOURCES:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rc $@ $?

$(OBJDIR):
	mkdir -p $(OBJDIR)

bonus: $(OBJECTS) $(BOBJECTS)
	ar rc $(NAME) $?

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
