CC = gcc
CFLAGS = -Wall -Wextra -Werror -MMD
NAME = libft.a

CHARA = chara/
GNL = gnl/
LIST = list/
MEMORY = memory/
PRINTF = printf/
STRING = string/
WRITE = write/

SRC_CHARA = $(CHARA)ft_isalpha.c \
			$(CHARA)ft_isdigit.c \
			$(CHARA)ft_isalnum.c \
			$(CHARA)ft_isascii.c \
			$(CHARA)ft_isprint.c \
			$(CHARA)ft_toupper.c \
			$(CHARA)ft_tolower.c

SRC_GNL = $(GNL)get_next_line.c \
			$(GNL)get_next_line_utils.c

SRC_LIST = $(LIST)ft_lstnew.c \
			$(LIST)ft_lstadd_front.c \
			$(LIST)ft_lstsize.c \
			$(LIST)ft_lstlast.c \
			$(LIST)ft_lstadd_back.c \
			$(LIST)ft_lstdelone.c \
			$(LIST)ft_lstclear.c \
			$(LIST)ft_lstiter.c

SRC_MEMORY = $(MEMORY)ft_bzero.c \
			$(MEMORY)ft_calloc.c \
			$(MEMORY)ft_memchr.c \
			$(MEMORY)ft_memcmp.c \
			$(MEMORY)ft_memcpy.c \
			$(MEMORY)ft_memmove.c \
			$(MEMORY)ft_memset.c

SRC_PRINTF = $(PRINTF)ft_printf.c \
			$(PRINTF)ft_conv_hexa.c \
			$(PRINTF)ft_hexa_address.c \
			$(PRINTF)ft_unsigned_itoa.c

SRC_STRING = $(STRING)ft_atoi.c \
			$(STRING)ft_strlen.c \
			$(STRING)ft_strlcpy.c \
			$(STRING)ft_strlcat.c \
			$(STRING)ft_strchr.c \
			$(STRING)ft_strrchr.c \
			$(STRING)ft_strncmp.c \
			$(STRING)ft_strnstr.c \
			$(STRING)ft_striteri.c \
			$(STRING)ft_strdup.c \
			$(STRING)ft_substr.c \
			$(STRING)ft_strjoin.c \
			$(STRING)ft_strtrim.c \
			$(STRING)ft_split.c \
			$(STRING)ft_itoa.c \
			$(STRING)ft_strmapi.c

SRC_WRITE = $(WRITE)ft_putchar_fd.c \
			$(WRITE)ft_putstr_fd.c \
			$(WRITE)ft_putendl_fd.c \
			$(WRITE)ft_putnbr_fd.c

ALL_OBJ = $(SRC_CHARA:.c=.o) \
			$(SRC_STRING:.c=.o) \
			$(SRC_MEMORY:.c=.o) \
			$(SRC_WRITE:.c=.o) \
			$(SRC_LIST:.c=.o) \
			$(SRC_PRINTF:.c=.o) \
			$(SRC_GNL:.c=.o)

ALL_DEP = $(SRC_CHARA:.c=.d) \
			$(SRC_STRING:.c=.d) \
			$(SRC_MEMORY:.c=.d) \
			$(SRC_WRITE:.c=.d) \
			$(SRC_LIST:.c=.d) \
			$(SRC_PRINTF:.c=.d) \
			$(SRC_GNL:.c=.d)

all : $(NAME)

$(NAME) : $(ALL_OBJ) libft.h
	@ar rcs $(NAME) $(ALL_OBJ)

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@rm -f $(ALL_OBJ) $(ALL_DEP)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re
