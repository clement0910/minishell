/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:33:02 by csapt             #+#    #+#             */
/*   Updated: 2021/06/16 18:03:40 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "shell_env.h"
# include "shell_parse.h"
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>

typedef struct s_global
{
	t_env	*env;
	char 	**tab_env;
	int		ret;
}				t_global;

//INIT SHELL
int init_var(t_global *glb, char **envp);

//Utilities
char *current_path(void);
char *get_latest_folder(char **folders);
char*current_folder(void);
void	print_cursor(int ret);
void print_welcome(void);

// Parse
char**** parse_command(t_global *glb, char *buff);
void fill_replaced1(t_global *glb, char **replaced, char *str, int *i);
void fill_replaced2(t_global *glb, char **replaced, char c);
void	fill_res(t_global *glb, char ***res, char *cmdsBis, int x);
void	fill_res1(t_global *glb, char ****res, char *cmds, int i);
char	*replace_vars(char *str, t_global *glb);

//QUIT SHELL
int 	ret_errno_msg(char *msg, int ret);
int 	free_shell(t_global *glb);
int 	ret_msg(char *msg, int ret);
void 	free_env(void *content);
void 	unknown_command_msg(char *command);

//SHELL COMMAND
int	execve_command(char *path_command, char **command, char **envp, int *ret);
char **get_path(char *path);
int check_another_path(char *path, char **path_command, char *command);
char *search_path_command(t_env *env, char *command, char **path);
int launch_command(t_global *glb, char **cmds);

//EXPORT
char **create_export_tab(t_env *env);
char *create_export_env(t_env_var *env);
int sort_ascii_tab(char **tab);

//OTHERS
int check_var_name(char *str_env);
int export_error_msg(char *str_env);

# include "shell_builtin.h"

#endif
