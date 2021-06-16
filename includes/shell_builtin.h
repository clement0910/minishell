/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_builtin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:20:43 by csapt             #+#    #+#             */
/*   Updated: 2021/06/16 15:17:17 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_BUILTIN_H
# define SHELL_BUILTIN_H

# include "shell_parse.h"
# include <dirent.h>

int		built_in_export(bool exported, char *str_env,
					 t_env **env, char ***env_tab);

int		built_in_env(char **tab_env);

int		built_in_hello(void);

int		built_in_unset(char *var_name, char ***env_tab, t_env **env);

int		built_in_echo(char **argv);
void	print_echo_str(char *str);
void	print_backslash(const char *str, int *i, int quote);
void	print_quotes(const char *str, int *i);
void	print_double_quotes(const char *str, int *i);

int		built_in_cd(char *path, t_env *env, char ***env_tab);
int		update_pwd(t_env *env, char ***env_tab);

int		built_in_pwd(void);

int		built_in_ls(void);
void	print_ls(struct dirent *tmp, DIR *folder);

#endif