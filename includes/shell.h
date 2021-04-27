/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:33:02 by csapt             #+#    #+#             */
/*   Updated: 2021/04/27 17:37:51 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "shell_env.h"
# include "shell_parse.h"
# include <string.h>
# include <sys/errno.h>

typedef struct s_global
{
	t_parse *command;
	t_env	*env;
	char 	**tab_env;
	int		ret;
}				t_global;


//INIT SHELL
int init_var(t_global *glb, char **envp);

//QUIT SHELL
int 	ret_errno_msg(char *msg, int ret);
int 	free_shell(t_global *glb);
int 	ret_msg(char *msg, int ret);

# include "shell_builtin.h"

#endif
