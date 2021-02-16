/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:01:37 by csapt             #+#    #+#             */
/*   Updated: 2021/02/16 16:52:18 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENV_H
#define SHELL_ENV_H

#include "libft.h"

typedef t_list t_envlst;

typedef struct s_env_var
{
	char *key;
	char *value;
	bool local;
}				t_env_var;

typedef struct s_env
{
	char **env_tab;
	t_envlst *env_lst;
	//t_envlst *env_lst_ascii; more opti ?
}				t_env;

int			get_path(char **env, char ***path);

t_env_var 	*get_env_data(char *envp);
int			env_to_lst(t_envlst **env, char *envp);
int			get_env(t_envlst **env, char **envp);

int			get_var_from_env(char **env, char **var, char *str);

#endif