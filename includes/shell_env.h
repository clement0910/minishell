/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:41:59 by csapt             #+#    #+#             */
/*   Updated: 2021/04/27 16:57:00 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENV_H
# define SHELL_ENV_H

typedef t_list t_env;

typedef struct s_env_var
{
	char *key;
	char *value;
	int exported;
}				t_env_var;

t_env_var *get_env_var(char *str_env, int exported);
char**	env_to_tab(t_env *lst);
t_env *env_to_null_lst(char *envp);
int	env_to_lst(t_env **env, char *envp);
t_env *get_env(char **envp);

#endif