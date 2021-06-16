/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:03:06 by rolaforg          #+#    #+#             */
/*   Updated: 2021/06/16 13:09:11 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	contain_var(char const *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if ((str[i] == '$' && i == 0) || (str[i] == '$' && str[i - 1] != '\\'))
			return (1);
		i++;
	}
	return (0);
}

char	*replace_vars(char *str, t_global *glb)
{
	int		i;
	char	*replaced;

	i = 0;
	replaced = NULL;
	if (!str || str[0] == '\'' || !contain_var(str))
		return (str);
	while (str[i])
	{
		if (str[i] == '$' && i == 0 || str[i] == '$' && str[i - 1] != '\\')
		{
			fill_replaced1(glb, &replaced, str, &i);
		}
		else
		{
			fill_replaced2(glb, &replaced, str[i]);
			i++;
		}
	}
	return (replaced);
}

int	check_and(char const *buff)
{
	size_t	i;

	i = ft_strlen(buff) - 1;
	if (i <= 0)
		return (0);
	while (buff[i] && ft_isws(buff[i]))
		i--;
	if (buff[i] == '&')
		return (1);
	return (0);
}

char	****parse_command(t_global *glb, char *buff)
{
	int		i;
	char	**cmds;
	char	****res;

	cmds = NULL;
	res = NULL;
	if (!buff || check_quotes_and_backslash(buff) || check_and(buff))
		return (NULL);
	cmds = strmbtok(buff, ";", "\"\'", "\"\'");
	res = malloc(sizeof(char ***) * (ft_tablen(cmds) + 1));
	if (cmds)
	{
		i = 0;
		while (cmds[i])
		{
			fill_res1(glb, res, cmds[i], i);
			i++;
		}
		res[i] = NULL;
	}
	ft_free_tab(cmds);
	return (res);
}
