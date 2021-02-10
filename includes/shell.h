/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:13:38 by csapt             #+#    #+#             */
/*   Updated: 2021/02/10 14:24:51 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include "shell_env.h"
#include "shell_command.h"
#include "shell_builtin.h"

#include "libft.h"
#include <sys/stat.h> //stat
#include <string.h>
#include <errno.h>
#include <dirent.h> //dir

typedef struct s_global
{
	char **path;
	char *buf;
	char **env;
	char **command; //reorganize struct ?
	char *cwd;
	int ret;
	char *home;
	t_envlst *env_list;
}				t_global;

int			init_shell(t_global *glb);
int			launch_shell(t_global *glb);

int			parse_command(char ***command, char *buf);
int			built_in_command(t_global *glb);

int			launch_command(t_global *glb);

int			free_shell(t_global *glb);
int			return_message_int(char *str, int ret);
int 		return_strerror(void);

void		print_lst_tab(t_envlst **yolo);
char 		**ft_lst_to_tab(t_envlst **lst);
#endif