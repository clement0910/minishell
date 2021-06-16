#include "shell.h"

void	fill_res(t_global *glb, char ***res, char *cmdsBis, int x)
{
	int		y;
	char	**args;

	args = strmbtok(cmdsBis, " ", "\"\'", "\"\'");
	y = 0;
	res[x] = malloc(sizeof(char *) * (ft_tablen(args) + 1));
	while (args[y])
	{
		if (replace_vars(args[y], glb))
			res[x][y] = ft_strdup(replace_vars(args[y], glb));
		else
			res[x][y] = ft_strdup("");
		y++;
	}
	res[x][y] = NULL;
	ft_free_tab(args);
}

void	fill_res1(t_global *glb, char ****res, char *cmds, int i)
{
	int		x;
	char	**cmdsBis;

	cmdsBis = strmbtok(cmds, "&", "\"\'", "\"\'");
	res[i] = malloc(sizeof(char **) * (ft_tablen(cmdsBis) + 1));
	x = 0;
	while (cmdsBis && cmdsBis[x])
	{
		fill_res(glb, res[i], cmdsBis[x], x);
		x++;
	}
	res[i][x] = NULL;
	ft_free_tab(cmdsBis);
}

char	*str_clean(char *str, char *chars)
{
	char	**tmp;
	int		i;

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
	return (tmp[0]);
}

void	fill_replaced1(t_global *glb, char **replaced, char *str, int *i)
{
	char	**tmp;
	char	*tmpBis;

	tmp = ft_split(str + *i, ' ');
	if (tmp[0][1] == '?')
	{
		if (*replaced)
			*replaced = ft_strfreejoin(*replaced, ft_itoa(glb->ret));
		else
			*replaced = ft_strdup(ft_itoa(glb->ret));
		*i += 2;
	}
	else
	{
		tmpBis = str_clean(tmp[0], "?!\"#$%&\'()*+,-./:;<=>@[\\]^_`{|}~");
		if (*replaced && tmpBis && get_var_value(glb->env, tmpBis))
			*replaced = ft_strfreejoin(*replaced, get_var_value
					(glb->env, tmpBis));
		else if (!*replaced && tmpBis && get_var_value(glb->env, (tmpBis)))
			*replaced = ft_strdup(get_var_value(glb->env, (tmpBis)));
		*i += ft_strlen(tmpBis) + 1;
		free(tmpBis);
	}
	ft_free_tab(tmp);
}

void	fill_replaced2(t_global *glb, char **replaced, char c)
{
	int		y;
	char	*replacedTmp;

	if (*replaced)
	{
		replacedTmp = ft_strdup(*replaced);
		free(*replaced);
	}
	else
		replacedTmp = ft_strdup("");
	replaced = malloc(sizeof(char) * (ft_strlen(replacedTmp) + 2));
	if (!*replaced)
		ft_putendl_fd("Fucked up\n", 1);
	y = 0;
	while (replacedTmp[y])
	{
		*replaced[y] = replacedTmp[y];
		y++;
	}
	free(replacedTmp);
	*replaced[y++] = c;
	*replaced[y] = '\0';
}
