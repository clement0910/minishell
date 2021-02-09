/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:13:38 by csapt             #+#    #+#             */
/*   Updated: 2021/02/09 15:36:59 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include "libft.h"
#include <sys/stat.h> //stat
#include <string.h>
#include <errno.h>
#include <dirent.h> //dir

typedef t_list t_envlst;

typedef struct s_global
{
	char **path;
	char *buf;
	char **env;
	char **command; //command et main command in same struct
	char *main_command;
	char *cwd;
	int ret;
	struct stat file;
	char *home;
	t_envlst *env_list;
}				t_global;

typedef struct s_env
{
	char *key;
	char *value;
}				t_env;


int			ft_echo(char **command);
int			ft_pwd(char *cwd);
int			free_shell(t_global *glb);
int			get_path(char **env, char ***path);
int			parse_command(t_global *glb);
int			return_message_int(char *str, int ret);
int 		return_strerror(void);
int			execute_command(t_global *glb);
int			launch_shell(t_global *glb);
int			execve_command(char *path_command, char **command, char **envp, int *ret);
int			init_shell(t_global *glb);
int			built_in_command(t_global *glb);
int			real_excve_command(char *command, t_global *glb);
int			start_shell(t_global *glb);
int			built_in_cd(t_global *glb);
int			get_home(char **env, char **home);
int			get_env(t_envlst **env, char **envp);
void		print_lst_tab(t_envlst **yolo);
t_env 		*get_env_value(char *envp);
int			ft_export(t_global *glb);
char 		**ft_strtabdup(char **src);
char 		**ft_lst_to_tab(t_envlst **lst);
int			ft_unset(t_global *glb, t_envlst **lst);
#endif