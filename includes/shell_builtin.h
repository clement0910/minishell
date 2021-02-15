/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:48:28 by csapt             #+#    #+#             */
/*   Updated: 2021/02/15 15:59:18 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_BUILTIN_H
# define SHELL_BUILTIN_H

#include "shell_env.h"

int			built_in_echo(char **command);

int			built_in_pwd(char **cwd);

int			built_in_cd(char **command, char *home);

int 		built_in_export(char **command, t_env *env);
int			print_declare(t_envlst **env_lst);

int			built_in_unset(char **command, t_env *env);

int			built_in_env(char **env_tab);

#endif