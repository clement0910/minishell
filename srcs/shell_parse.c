/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:03:06 by rolaforg          #+#    #+#             */
/*   Updated: 2021/06/11 14:32:13 by csapt            ###   ########lyon.fr   */
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

char    **strmbtiktok ( char *input, char *delimit, char *openblock, char
*closeblock) {
    char **res = NULL;
    char **tmp;
    char *t = NULL;
    char *lead = NULL;
    char *block = NULL;
    int iBlock = 0;
    int iBlockIndex = 0;

    if (input != NULL) {
        t = input;
        lead = input;
    }

    while (lead)
    {
        lead = t;
        if ( *t == '\0') {
            lead = NULL;
        }
        while ( *t != '\0') {
            if ( iBlock) {
                if ( closeblock[iBlockIndex] == *t) {
                    iBlock = 0;
                }
                t++;
                continue;
            }
            if ( ( block = strchr ( openblock, *t)) != NULL) {
                iBlock = 1;
                iBlockIndex = block - openblock;
                t++;
                continue;
            }
            if ( strchr ( delimit, *t) != NULL) {
                if (strchr ( delimit, *t + 1) == NULL)
                    *t = '\0';
                else
                    t++;
                t++;
                break;
            }
            t++;
        }
        //lft_putendl_fd(lead, 1);
        if (lead && ft_strlen(lead)) {
            int i = 0;
            //int x = 0;
            if (res && res[0] && ft_tablen(res))
            {
                tmp = ft_strtabdup(res);
                ft_free_tab(res);
                if (!tmp)
                    ft_putendl_fd("Cannot dup", 1);
                res = malloc(sizeof(char*) * (ft_tablen(tmp) + 2));
                while (tmp[i] && tmp[i][0]) {
                    res[i] = ft_strdup(tmp[i]);
                    i++;
                }
                ft_free_tab(tmp);
            } else {
                res = malloc(sizeof(char*) * 2);
            }
            res[i++] = ft_strdup(lead);
            res[i] = NULL;
        }
    }
    return res;
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
	while (buff[i] && ft_isws(buff[i]))
		i--;
	if (buff[i - 1] == '&' && buff[i] == '&')
		return (1);
	return (0);
}

int     check_quotes(char const *buff)
{
	int i;
	int singleCnt;
	int	doubleCnt;

	i = 0;
    singleCnt = 0;
    doubleCnt = 0;

	while (buff[i])
	{
		if (buff[i] == '\'' && (buff[i - 1] != '\\' || (buff[i - 1] == '\\' && buff[i - 2] == '\\')) && singleCnt < 2)
			singleCnt++;
		else if (buff[i] == '\'' && (buff[i - 1] != '\\' || (buff[i - 1] == '\\' && buff[i - 2] == '\\')) && singleCnt == 2)
			singleCnt = 1;
		else if (buff[i] == '"' && (buff[i - 1] != '\\' || (buff[i - 1] == '\\' && buff[i - 2] == '\\')) && doubleCnt < 2)
			doubleCnt++;
		else if (buff[i] == '"' && (buff[i - 1] != '\\' || (buff[i - 1] == '\\' && buff[i - 2] == '\\')) && doubleCnt == 2)
			doubleCnt = 1;
		i++;
	}
	if (singleCnt == 1 || doubleCnt == 1)
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

    if (!buff || check_quotes(buff) || check_and(buff))
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