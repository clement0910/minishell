/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:48:28 by csapt             #+#    #+#             */
/*   Updated: 2021/02/10 14:33:11 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_BUILTIN_H
# define SHELL_BUILTIN_H

#include "shell_env.h"

int			built_in_echo(char **command);
int			built_in_pwd(char **cwd);
int			built_in_cd(char **command, char *home);
int 		built_in_export(char **command, char ***env_tab, t_envlst **env_list);
int			built_in_unset(char **command, char ***env_tab, t_envlst **lst);
#endif