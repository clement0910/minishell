/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:20:43 by csapt             #+#    #+#             */
/*   Updated: 2021/04/29 14:51:34 by rolaforg         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_BUILTIN_H
# define SHELL_BUILTIN_H

#include "shell_parse.h"

int built_in_command(char *cmd, char **args, t_global *glb);
int	built_in_export(int exported, char *str_env, t_env **env, char ***env_tab);
int built_in_env(char **tab_env);
int built_in_hello(void);
int built_in_unset(char *var_name, char ***env_tab, t_env **env);
int	built_in_echo(char **args);
int	built_in_cd(char *path, char *home);
int	built_in_pwd(void);

#endif