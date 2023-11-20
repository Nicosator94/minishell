/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niromano <niromano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:20:25 by niromano          #+#    #+#             */
/*   Updated: 2023/11/20 13:18:27 by niromano         ###   ########.fr       */
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
	t_env	*env;
	int		exit_status;
	int		stdin;
	int		stdout;
}	t_mini;

extern int	g_signal;
void	sigint(int code);
void	sigquit(int code);
void	check_signal(t_mini *minishell);

t_env	*create_own_env(char **env);
t_env	*create_without_env(void);
t_env	*fill_env(char **tmp);
void	add_shlvl(t_env *env);
char	**list_to_matrix(t_mini *minishell);

int		syntax_error_check(char *s);
int		check_pipes(char *s);
int		check_multi_pipes(char *s);
int		check_brackets_before_pipes(char *s);
int		check_quotes(char *s);
int		check_brackets(char *s);
int		check_multi_brackets(char *s);
int		check_space_brackets(char *s);
int		check_opposite_brackets(char *s);
int		check_spaces(char *s);
int		passes_quotes(char *s, int i);

t_cmd	*parsing(char *s, t_mini *minishell);
int		pass_quotes(char *s, int i);
char	*init_new_cmd(char *s, int i, t_cmd *cmd);
void	add_null_cmd(t_cmd *cmd);

void	expend(t_mini *minishell);
char	*replace_with_env_utils(char *s, char *tmp1, char *tmp2);
char	*replace(char *name, t_env *env, int *exit_status);
int		dollar_len(char *s, int i);

void	treatment_cmd(t_mini *minishell);
int		get_file(t_cmd *cmd, int i, t_mini *minishell);
int		get_command(t_cmd *cmd, int i, t_mini *minishell);
void	fill_mat_of_cmd(t_cmd *cmd, t_mini *minishell);
void	set_redi(t_cmd *cmd, t_mini *minishell);

void	create_here_doc(t_mini *minishell);
char	*expend_in_heredoc(char *s, t_mini *minishell);
void	clean_here_doc(t_cmd *cmd);

void	all_clear_command(t_env *env, t_cmd *cmd);

void	exec(t_mini *minishell);
int		take_infile(t_cmd *cmd, int tmp_file);
int		take_outfile(t_cmd *cmd, int last);
char	*get_path(char *cmd, t_mini *minishell);
void	wait_all(t_mini *minishell);

int		check_builtin(char *main_cmd);
int		do_builtin(t_cmd *cmd, t_mini *minishell);
void	do_builtin_in_exec(t_cmd *cmd, t_mini *minishell);

int		pwd(void);
int		my_env(t_env *env);
int		my_echo(char **cmd);
int		cd(char **cmd, t_env **env);
int		unset(char **cmd, t_env **env);
int		my_exit(char **cmd);

int		export(char **cmd, t_env **env);
int		check_occurence(t_env **env, t_env *new);
int		print_sort_list(t_env *env);
char	*get_name(char *s);
char	*get_value(char *s);
void	add_back(t_env **lst, t_env *new);
t_env	*new_element(char *name, char *value, char *cmd);

int		size_env(t_env *env);

void	clear_all(t_mini *minishell);
void	clear_all_malloc_failed(t_mini *minishell);
void	clear_env(t_env *env);
void	clear_cmd(t_cmd *cmd);
void	clear_list_cmd(t_list *l_cmd);
void	clear_mat(char **mat);
void	clear_redi(t_redi *redi);

#endif