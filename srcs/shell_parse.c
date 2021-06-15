/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:03:06 by rolaforg          #+#    #+#             */
/*   Updated: 2021/06/15 17:40:27 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int     contain_var(char const *str)
{
    int i;

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


char    *str_clean(char *str, char *chars)
{
    char    **tmp;
    int     i;

    tmp = NULL;
    i = 0;
    while (chars[i])
    {
        if (!tmp)
            tmp = ft_split(str, chars[i]);
        else
            tmp = ft_split(tmp[0], chars[i]);
        i++;
    }
    return tmp[0];
}

char    *replace_vars(char *str, t_global *glb)
{
    size_t  i;
    size_t  y;
    char    *replaced;
    char    *replacedTmp;
    char    **tmp;
    char    *tmpBis;

    i = 0;
    replaced = NULL;
    if (!str || str[0] == '\'' || !contain_var(str))
        return str;
    while (str[i])
    {
        if (str[i] == '$' && i == 0 || str[i] == '$' && str[i - 1] != '\\')
        {
            tmp = ft_split(str + i, ' ');
            if (replaced && tmp[0][1] == '?') {
                replaced = ft_strfreejoin(replaced, ft_itoa(glb->ret));
                i += 2;
            }
            else if (!replaced && tmp[0][1] == '?') {
                replaced = ft_strdup(ft_itoa(glb->ret));
                i += 2;
            }
            else {
                tmpBis = str_clean(tmp[0], "?!\"#$%&\'()*+,-./:;<=>@[\\]^_`{|}~");
                if (replaced && tmpBis && get_var_value(glb->env, tmpBis))
                    replaced = ft_strfreejoin(replaced, get_var_value
                    (glb->env, tmpBis));
                else if (!replaced && tmpBis && get_var_value(glb->env, (tmpBis)))
                    replaced = ft_strdup(get_var_value(glb->env, (tmpBis)));
                i += ft_strlen(tmpBis) + 1;
                free(tmpBis);
            }
            ft_free_tab(tmp);
        }
        else {
            if (replaced) {
                replacedTmp = ft_strdup(replaced);
                free(replaced);
            }
            else
                replacedTmp = ft_strdup("");
            replaced = malloc(sizeof(char) * (ft_strlen(replacedTmp) + 2));
            if (!replaced)
                ft_putendl_fd("Fucked up\n", 1);
            y = 0;
            while (replacedTmp[y]) {
                replaced[y] = replacedTmp[y];
                y++;
            }
            free(replacedTmp);
            replaced[y++] = str[i];
            replaced[y] = '\0';
            i++;
        }
    }
    return replaced;
}

int     check_and(char const *buff)
{
    size_t 	i;

	i = ft_strlen(buff) - 1;
	if (i <= 0)
		return (0);
	while (buff[i] && ft_isws(buff[i]))
		i--;
	if (buff[i] == '&')
		return (1);
	return (0);
}

char**** parse_command(t_global *glb, char *buff)
{
    int i;
    int x;
    int y;
    char	**cmds = NULL;
    char	**cmdsBis = NULL;
    char	**args = NULL;
    char	****res = NULL;

    printf("%s\n", buff);
    if (!buff || check_quotes_and_backslash(buff) || check_and(buff))
        return (NULL);
    cmds = strmbtok(buff, ";", "\"\'", "\"\'");
    res = malloc(sizeof(char***) * (ft_tablen(cmds) + 1)); // RES
    if (cmds)
    {
        i = 0;
        while (cmds[i])
        {
            cmdsBis = strmbtok(cmds[i], "&", "\"\'", "\"\'");
            res[i] = malloc(sizeof(char**) * (ft_tablen(cmdsBis) + 1)); // RES
            x = 0;
            while (cmdsBis && cmdsBis[x])
            {
                args = strmbtok(cmdsBis[x], " ", "\"\'", "\"\'");
                y = 0;
                res[i][x] = malloc(sizeof(char*) * (ft_tablen(args) + 1));
                while (args[y])
                {
                    if (replace_vars(args[y], glb))
                        res[i][x][y] = ft_strdup(replace_vars(args[y], glb));
                    else
                        res[i][x][y] = ft_strdup("");
                    y++;
                }
                res[i][x][y] = NULL;
                ft_free_tab(args);
                x++;
            }
            res[i][x] = NULL;
            ft_free_tab(cmdsBis);
            i++;
        }
        res[i] = NULL;
    }
    ft_free_tab(cmds);
    return (res);
}