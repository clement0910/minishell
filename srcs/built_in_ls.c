
#include "shell.h"

void	print_ls(struct dirent *tmp, DIR *folder)
{
	tmp = readdir(folder);
	while (tmp)
	{
		if (tmp->d_type == 4 && tmp->d_name[0] != '.')
			ft_putstr_fd(C_YB, 1);
		else if (tmp->d_type == 4)
			ft_putstr_fd(C_RB, 1);
		else if (tmp->d_type == 8)
			ft_putstr_fd(C_BB, 1);
		ft_putstr_fd(tmp->d_name, 1);
		ft_putendl_fd(C_N, 1);
		tmp = readdir(folder);
	}
}

int	built_in_ls(void)
{
	struct dirent	*tmp;
	DIR				*folder;

	folder = opendir(".");
	if (folder == NULL)
	{
		ft_putendl_fd("Cannot ls", 1);
		return (1);
	}
	else
	{
		print_ls(tmp, folder);
		return (0);
	}
	closedir(folder);
	return (0);
}
