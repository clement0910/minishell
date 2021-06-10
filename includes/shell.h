/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 19:33:02 by csapt             #+#    #+#             */
/*   Updated: 2021/04/29 15:16:19 by rolaforg         ###   ########lyon.fr   */
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
	t_parse *p;
	t_env	*env;
	char 	**tab_env;
	int		ret;
}				t_global;


//INIT SHELL
int init_var(t_global *glb, char **envp);

//Utilities
char *current_path(void);
char	*current_folder(void);
void	print_cursor(int ret);
void print_welcome(void);

// Parse
int 	parse_command(t_global *glb, char *buff);

//QUIT SHELL
int 	ret_errno_msg(char *msg, int ret);
int 	free_shell(t_global *glb);
int 	ret_msg(char *msg, int ret);
void 	free_env(void *content);
# include "shell_builtin.h"

#endif
