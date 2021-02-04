/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:13:38 by csapt             #+#    #+#             */
/*   Updated: 2021/02/04 16:41:29 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include "libft.h"
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
typedef struct s_global
{
	char **env;
	char **path;
	char *buf;
	char **command; //command et main command in same struct
	char *main_command;
	char *cwd;
	pid_t pid;
}				t_global;


int			ft_echo(char **command);
int			ft_pwd(char *cwd);
int			free_shell(t_global *glb);
int			get_path(char **env, char ***path);
int			parse_command(t_global *glb);
int			return_message_int(char *str, int ret);
int 		return_strerror(void);
int			execute_command(t_global *glb);
int			launch_shell(t_global *glb);
int			excve_command(t_global *glb);
int			init_shell(t_global *glb);
int			built_in_command(t_global *glb);
int	real_excve_command(char *command, t_global *glb);
int			start_shell(t_global *glb);
#endif