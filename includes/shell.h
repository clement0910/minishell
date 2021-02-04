/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:13:38 by csapt             #+#    #+#             */
/*   Updated: 2021/02/04 11:11:59 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include "libft.h"
#include <string.h>
#include <errno.h>
typedef struct s_global
{
	char **env;
	char **path;
	char *buf;
	char **command; //mettre command et main command
	char *main_command;
	char *cwd;
	pid_t pid;
}				t_global;


int		ft_echo(char **command);
int			ft_pwd(char *cwd);
int		free_shell(t_global *glb);
int		get_path(char **env, char ***path);
int		parse_command(t_global *glb);
int		return_message_int(char *str, int x);
int 	return_strerror(void);
int	execute_command(t_global *glb);
int	read_shell(t_global *glb);
int	init_shell(t_global *glb);
int	built_in_command(t_global *glb);
#endif