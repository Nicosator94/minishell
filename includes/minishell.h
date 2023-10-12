/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:20:25 by niromano          #+#    #+#             */
/*   Updated: 2023/10/12 11:02:10 by niromano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

# include "../libft/libft.h"

# define INPUT 1;
# define OUTPUT 2;
# define HEREDOC 3;
# define APPEND 4;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redi
{
	char			*file;
	int				status;
	struct s_redi	*next;
}	t_redi;

typedef struct s_cmd
{
	char			*line;
	t_list			*l_cmd;
	char			**cmd;
	t_redi			*file;
	struct s_cmd	*next;
}	t_cmd;

t_env	*create_own_env(char **env);
t_env	*create_without_env(void);
t_env	*fill_env(char **tmp);
void	clear_env(t_env *env);
char	**list_to_matrix(t_env *env);

int		syntax_error_check(char *s);
int		check_brackets(char *s);
int		check_multi_brackets(char *s);
int		check_space_brackets(char *s);
int		check_opposite_brackets(char *s);

t_cmd	*parsing(char *s, t_env *env);
int		pass_quotes(char *s, int i);
char	*init_new_cmd(char *s, int i, t_cmd *cmd);
void	add_null_cmd(t_cmd *cmd);

void	expend(t_cmd *line, t_env *env);
char	*replace_with_env_utils(char *s, char *tmp1, char *tmp2);
char	*replace(char *name, t_env *env);
int		dollar_len(char *s, int i);

void	treatment_cmd(t_cmd *cmd, t_env *env);
int		get_file(t_cmd *cmd, int i, t_env *env, t_cmd *start_cmd);
int		get_command(t_cmd *cmd, int i, t_env *env, t_cmd *start_cmd);
void	fill_mat_of_cmd(t_cmd *cmd, t_env *env, t_cmd *start_cmd);
void	set_redi(t_cmd *cmd, t_env *env, t_cmd *start_cmd);

void	all_clear_command(t_env *env, t_cmd *cmd);

#endif