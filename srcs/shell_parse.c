/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rolaforg <rolaforg@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:03:06 by rolaforg          #+#    #+#             */
/*   Updated: 2021/06/10 18:02:54 by csapt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// Check quotes closed
// Check something after && (non space)
// backslash avant quotes 
// backslash avant $ (env)
// If one cmd fail with && stop anb go to next ;

int contain_var(char const *str)
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

char *append_char(char *str, char c)
{
    char *tmp;

    tmp = malloc(sizeof(char) * (ft_strlen(str) + 2));
    if (!tmp)
        return (NULL);
    tmp = ft_strcpy(str, tmp);
    tmp[ft_strlen(str)] = c;
    tmp[ft_strlen(str) + 1] = '\0';
    return (tmp);
}

char **strmbtiktok ( char *input, char *delimit, char *openblock, char
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

char *str_clean(char *str, char *chars)
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

char    *replace_vars(char *str)
{
    size_t  i;
    size_t  y;
    char    *replaced;
    char    *replacedTmp;
    char    **tmp;
    char    *tmpBis;

    i = 0;
    replaced = NULL;
    if (!str || !contain_var(str))
        return str;
    while (str[i])
    {
        if (str[i] == '$' && i == 0 || str[i] == '$' && str[i - 1] != '\\')
        {
            //ft_putendl_fd("VVVV", 1);

            tmp = ft_split(str + i, ' ');
            //tmp = strmbtiktok(tmp[0], " $", "", "");
            tmpBis = str_clean(tmp[0], "!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~");
            ft_putendl_fd(tmp[0], 1);
            ft_putendl_fd(tmpBis, 1);
            //tmpBis = ft_split(tmp[0], '"');
            //tmpBis = ft_split(tmpBis[0], '\'');
            //tmpBis = strmbtiktok(tmp[0], "\"\'^{}(),.;@#&", "", "");
            ft_putendl_fd(tmpBis, 1);
            //ft_putendl_fd("---", 1);
            //int a = 0;
            //while (tmpBis[a])
                //ft_putendl_fd(tmpBis[a++], 1);
            if (replaced && tmp && getenv(tmpBis))
                replaced = ft_strfreejoin(replaced, getenv(tmpBis));
            else
                replaced = ft_strdup(" ");
            i += ft_strlen(tmpBis) + 1;
            ft_free_tab(tmp);
            //ft_free_tab(tmpBis);
            //ft_putendl_fd("^^^^", 1);
        }
        else {
            if (replaced) {
                replacedTmp = ft_strdup(replaced);
                free(replaced);
            }
            else
                replacedTmp = ft_strdup(" ");
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

char    **replace_vars_tab(char **tab)
{
    size_t i;
    char **res;

    res = NULL;
    if (tab) {
        i = 0;
        res = malloc(sizeof(char*) * (ft_tablen(tab) + 1));
        if (!res)
            return NULL;
        while (tab[i]) {
            if (tab[i][0] == '\'') {
                ft_putendl_fd("if", 1);
                ft_putendl_fd(tab[i], 1);
                res[i] = ft_strdup(tab[i]);
            }
            else {
                ft_putendl_fd("else", 1);
                ft_putendl_fd(tab[i], 1);
                res[i] = replace_vars(tab[i]);
            }
            i++;
        }
        res[i] = NULL;
        //ft_free_tab(tab);
    }
    return res;
}

int check_and(char const *buff)
{
    size_t 	i;

	i = ft_strlen(buff) - 1;
	while (buff[i] && ft_isws(buff[i]))
		i--;
	if (buff[i - 1] == '&' && buff[i] == '&')
		return (1);
	return (0);
}

int check_quotes(char const *buff)
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

char *strmbtok ( char *input, char *delimit, char *openblock, char *closeblock) {
    static char *token = NULL;
    char *lead = NULL;
    char *block = NULL;
    int iBlock = 0;
    int iBlockIndex = 0;

    if ( input != NULL) {
        token = input;
        lead = input;
    }
    else {
        lead = token;
        if ( *token == '\0') {
            lead = NULL;
        }
    }

    while ( *token != '\0') {
        if ( iBlock) {
            if ( closeblock[iBlockIndex] == *token) {
                iBlock = 0;
            }
            token++;
            continue;
        }
        if ( ( block = strchr ( openblock, *token)) != NULL) {
            iBlock = 1;
            iBlockIndex = block - openblock;
            token++;
            continue;
        }
        if ( strchr ( delimit, *token) != NULL) {
            *token = '\0';
            token++;
            break;
        }
        token++;
    }
    return lead;
}

size_t args_count(char *str)
{
    char *tmp = ft_strdup(str);
    size_t i;

    i = 0;

    strmbtok ( tmp, " ", "\"\'", "\"\'");
    while (strmbtok(NULL," ","\"\'","\"\'") !=
            NULL) {
        i++;
    }
    free(tmp);
    printf("Args count: %zu\n", i);
    return i;
}

int	parse_command(t_global *glb, char *buff)
{
    int i;
    int x;
    char	**cmds = NULL;
	char	**cmdsBis = NULL;
	char	**args = NULL;

	if (!buff || check_quotes(buff) || check_and(buff))
		return (1);
	cmds = replace_vars_tab(strmbtiktok(buff, ";", "\"\'", "\"\'")); // LEAK
	if (cmds)
	{
        i = 0;
        while (cmds[i])
        {
            cmdsBis = strmbtiktok(cmds[i], "&", "\"\'", "\"\'");
            x = 0;
            while (cmdsBis && cmdsBis[x])
            {
                args = strmbtiktok(cmdsBis[x], " ", "\"\'", "\"\'");
                if (args && args[0] && built_in_command(args[0], args + 1,
                                                        glb)) {
                    ft_putendl_fd("Unknown command.",1);
                }
                ft_free_tab(args);
                x++;
            }
            ft_free_tab(cmdsBis);
            i++;
        }
    }
	ft_free_tab(cmds);
    return (0);
}