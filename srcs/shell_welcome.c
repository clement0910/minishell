#include "shell.h"

void	print_welcome(void)
{
	ft_putstr_fd(C_GN, 1);
	ft_putendl_fd("Minishell.", 1);
	ft_putstr_fd(C_Y, 1);
	ft_putstr_fd(".:# By rolaforg and csapt #:.\n\n", 1);
	ft_putstr_fd(C_N, 1);
}
