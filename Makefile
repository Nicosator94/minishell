CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -g3

HEADERS = minishell.h

SOURCES = main.c \
		env.c \
		env_utils.c \
		env_w_env.c \
		syntax.c \
		parsing.c \
		parsing_utils.c \
		expend.c \
		treatment_cmd.c \
		get_file.c \
		get_command.c \
		all_clear_command.c

SRC = srcs/
DIR = objs_deps/
INC = includes/

INCLUDES = -I/$(INCS)

SRCS = $(addprefix $(SRC), $(SOURCES))
OBJS = $(addprefix $(DIR), $(OBJ))
DEPS = $(addprefix $(DIR), $(DEP))
INCS = $(addprefix $(INC), $(HEADERS))

OBJ = $(SOURCES:.c=.o)
DEP = $(SOURCES:.c=.d)

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS)
	@make -sC libft
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) ./libft/libft.a -lreadline
	@echo "Compilation completed"

$(DIR)%.o : $(SRC)%.c | $(DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(DIR) :
	@echo "Start Compilation for $(NAME)"
	@echo "Wait ..."
	@mkdir -p objs_deps

clean :
	@echo "Deleting Objects and Dependencies"
	@make fclean -sC libft
	@rm -rf $(DIR)

fclean : clean
	@echo "Deleting the executable"
	@rm -f $(NAME)

re : fclean all

-include $(DEPS)

.PHONY : all bonus clean fclean re