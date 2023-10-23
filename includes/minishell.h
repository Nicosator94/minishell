/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:20:25 by niromano          #+#    #+#             */
/*   Updated: 2023/10/23 11:41:36 by niromano         ###   ########.fr       */
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
	int				val;
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
	pid_t			pid;
}	t_cmd;

typedef struct s_mini
{
	t_cmd	*cmd;
	t_env	**env;
	int		exit_status;
}	t_mini;

t_env	*create_own_env(char **env);
t_env	*create_without_env(void);
t_env	*fill_env(char **tmp);
void	add_shlvl(t_env *env);
void	clear_env(t_env *env);
char	**list_to_matrix(t_env *env, t_cmd *start_cmd);

int		syntax_error_check(char *s);
int		check_quotes(char *s);
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

void	create_here_doc(t_cmd *start_cmd, t_env *env);
void	clean_here_doc(t_cmd *cmd);

void	all_clear_command(t_env *env, t_cmd *cmd);
void	all_free(t_env *env, t_cmd *cmd);

void	exec(t_cmd *cmd, t_env **env);
int		take_infile(t_cmd *cmd, int tmp_file);
int		take_outfile(t_cmd *cmd, int last);
char	*get_path(char *cmd, t_env *env);
void	wait_all(t_cmd *cmd);

int		check_builtin(char *main_cmd);
void	do_builtin(t_cmd *cmd, t_env **env, int trigger);

int				cd(char **cmd, t_env *env);
void			my_echo(char **cmd);
void			 my_env(char **cmd, t_env *env);
unsigned int 	my_exit(char **cmd, t_env *env);
void			pwd(char **cmd);
void			unset(char **cmd, t_env **env);

void	export(char **cmd, t_env *env);
void	print_sort_list(t_env *env);
char	*get_name(char *s);
char	*get_value(char *s);
void	add_back(t_env **lst, t_env *new);
t_env	*new_element(char *name, char *value, char *cmd);

int	size_env(t_env *env);

#endif