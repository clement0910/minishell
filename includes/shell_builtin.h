/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:20:43 by csapt             #+#    #+#             */
/*   Updated: 2021/04/28 16:19:45 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_BUILTIN_H
# define SHELL_BUILTIN_H

#include "shell_parse.h"

int built_in_command(t_global *env);
int	built_in_export(int exported, char *str_env, t_env **env, char ***env_tab);
int built_in_env(char **tab_env);
int built_in_hello(void);
int built_in_unset(t_parse *command, char ***env_tab, t_env **env);
#endif