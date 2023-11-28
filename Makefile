CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD -g3

HEADERS = minishell.h

SOURCES = main.c \
		clear.c \
		clear_utils.c \
		signal.c \
		env/env.c \
		env/env_utils.c \
		env/env_w_env.c \
		env/env_list_to_matrix.c \
		parsing/syntax.c \
		parsing/syntax_utils.c \
		parsing/syntax_utils_2.c \
		parsing/parsing.c \
		parsing/parsing_utils.c \
		expend/expend.c \
		expend/expend_utils.c \
		expend/replace_with_env.c \
		expend/split_all.c \
		expend/remove_quotes.c \
		expend/treatment_cmd.c \
		expend/treatment_cmd_utils.c \
		expend/get_file.c \
		expend/get_command.c \
		expend/create_here_doc.c \
		parsing/all_clear_command.c \
		exec/check_builtin.c \
		exec/exec_builtin.c \
		exec/exec_failed.c \
		exec/exec.c \
		exec/file.c \
		exec/get_path.c \
		exec/wait.c \
		builtin/cd.c \
		builtin/echo.c \
		builtin/env.c \
		builtin/exit.c \
		builtin/export_new_element.c \
		builtin/export_print.c \
		builtin/export.c \
		builtin/pwd.c \
		builtin/unset.c

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
	@mkdir -p objs_deps/builtin
	@mkdir -p objs_deps/env
	@mkdir -p objs_deps/exec
	@mkdir -p objs_deps/expend
	@mkdir -p objs_deps/parsing

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