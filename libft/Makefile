CC = clang

FLAGS = -Wall -Wextra -Werror

NAME = libft.a

SOURCES =   ft_realloc.c\
			ft_memset.c\
			ft_bzero.c\
            ft_memcpy.c\
            ft_memccpy.c\
            ft_memmove.c\
            ft_memchr.c\
            ft_memcmp.c\
            ft_strlen.c\
            ft_strdup.c\
            ft_strlcat.c\
            ft_strchr.c\
			ft_strcmp.c\
            ft_strrchr.c\
            ft_strnstr.c\
            ft_strncmp.c\
            ft_atoi.c\
            ft_isalpha.c\
            ft_isdigit.c\
            ft_isalnum.c\
            ft_isascii.c\
            ft_isprint.c\
            ft_toupper.c\
            ft_tolower.c\
            ft_strmapi.c\
            ft_substr.c\
            ft_strjoin.c\
            ft_strtrim.c\
            ft_split.c\
            ft_itoa.c\
			ft_putchar_fd.c\
            ft_putstr_fd.c\
			ft_putendl_fd.c\
			ft_putnbr_fd.c\
			ft_calloc.c\
			ft_strlcpy.c\
			ft_memdel.c\
			ft_strcat.c\
			ft_strcpy.c\
			ft_putstr.c\
			ft_strndup.c\

BONUSSRC = 	ft_lstadd_back_bonus.c\
			ft_lstadd_front_bonus.c\
			ft_lstdelone_bonus.c\
			ft_lstiter_bonus.c\
			ft_lstmap_bonus.c\
			ft_lstnew_bonus.c\
			ft_lstsize_bonus.c\
			ft_lstlast_bonus.c\
			ft_lstclear_bonus.c\

HEADERS = libft.h

OBJECT = $(SOURCES:.c=.o)

OBJECTBNS = $(BONUSSRC:.c=.o)

$(NAME): $(OBJECT) $(HEADERS)
	$(CC) $(FLAGS) -c $(SOURCES)
	ar rc $(NAME) $(OBJECT)
	ranlib $(NAME)

so:
	$(CC) -fPIC $(FLAGS) -c $(SOURCES)
	gcc -shared -o libft.so $(OBJECT)

all: $(NAME)

clean:
	rm -rf $(OBJECT) $(OBJECTBNS)

fclean: clean
	rm -fr $(NAME)

re: fclean all

bonus: $(OBJECTBNS) $(HEADERS)
	$(CC) $(FLAGS) -c $(BONUSSRC)
	ar rc $(NAME) $(OBJECTBNS)
	ranlib $(NAME)
