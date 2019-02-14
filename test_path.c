#include "./libft/includes/libft.h"

int main(int ac, char **av)
{
	if (ac > 1)
		printf("path: %s %s = %s\n", av[1], av[2], ft_exp_path(av[1], av[2]));
	return(0);
}