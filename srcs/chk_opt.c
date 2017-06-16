/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 23:25:32 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/16 02:48:07 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	check_next(char **av)
{
	char	*str;
	int		i;
	int		c;
	int		j;

	str = "-l1Rrat";
	i = 1;
	c = -1;
	j = 0;
	while (av[i])
	{
		while (av[i][j] && av[i][0] == '-')
		{
			c++;
			if (!str[c])
				ft_error("ls: illegal option\nusage: ls [Ralrt] [file ...]\n");
			if (str[c] == av[i][j])
			{
				j++;
				c = -1;
			}
		}
		j = 0;
		i++;
	}
}

int		check_options(char **av, char **options_set)
{
	int		i;
	char	*options;

	i = 0;
	options = ft_strdup("l1Rart");
	if (av[1])
	{
		if (av[1][0] != '-')
			return (1);
		check_next(av);
	}
	while (av[++i])
	{
		if (av[i][0] != '-')
			return (i);
		*options_set = ft_strjoin(*options_set, av[i]);
	}
	return (i);
}
