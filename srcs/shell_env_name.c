/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csapt <csapt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 15:26:15 by csapt             #+#    #+#             */
/*   Updated: 2021/06/11 15:28:27 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int check_var_name(char *str_env)
{
	int i;

	i = 0;
	if (!str_env)
		return (1);
	if (ft_isalpha(str_env[i]) == 0)
		return (1);
	while (str_env[i] != '=' && str_env[i] != '\0')
	{
		if (str_env[i] == '+' && str_env[i + 1] != '=')
			return (1);
		if (str_env[i] != '+' && ft_isalnum(str_env[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int export_error_msg(char *str_env)
{
	ft_putstr_fd("minishell: export: '", 1);
	ft_putstr_fd(str_env, 1);
	ft_putendl_fd("': not a valid identifier", 1);
	return (1);
}