/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:41:59 by csapt             #+#    #+#             */
/*   Updated: 2021/06/11 16:44:36 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_ENV_H
# define SHELL_ENV_H

typedef t_list t_env;

typedef struct s_env_var
{
	char *key;
	char *value;
	bool exported; //TODO: replace par bool
}				t_env_var;

//ENV FUNCS
t_env_var *get_env_var(char *str_env, bool exported);
t_env_var *get_env_var_null(char *var);
int	env_to_lst(t_env **env, char *envp);
t_env *env_to_null_lst(char *envp);
t_env *get_env(char **envp);

//UTILS
char *get_var_value(t_env *env, char *var_name);
int exported_env_len(t_env *env);
int check_exist_var(char *var_name, t_env *env, bool exported);
char**	env_to_tab(t_env *env);

//EXPORT ENV
int export_var(char *var, t_env **env, char ***env_tab);
int replace_env_value(char *str_env, t_env *env, char ***env_tab);
int export_env(char *str_env, t_env **env, char ***env_tab, bool exported);
int display_export(t_env *env);

//ADDBACK ENV
int addback_env(t_env_var *env_var, t_env **env);
int addback_env_value(char *str_env, t_env **env, char ***env_tab, bool exported);
int addback_value(char *str_env, t_env *env, char ***env_tab);
int check_addback(const char *str_env);

#endif