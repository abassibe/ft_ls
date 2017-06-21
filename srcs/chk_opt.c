/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 23:25:32 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/21 01:46:06 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	check_next(char **av, char *str, int i, int j)
{
	int		c;

	str = "-Rafglmrtu1";
	c = -1;
	while (av[i])
	{
		while (av[i][j] && av[i][0] == '-')
		{
			c++;
			if (!str[c])
			{
				write(2, "ls: illegal option\n", 19);
				write(2, "usage: ls [Rafglmrtu1] [file ...]\n", 34);
				exit(1);
			}
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
	options = ft_strdup("Rafglmrtu1");
	if (av[1])
	{
		if (av[1][0] != '-')
			return (1);
		check_next(av, options, i + 1, i);
	}
	while (av[++i])
	{
		if (av[i][0] != '-')
			return (i);
		*options_set = ft_strjoin(*options_set, av[i]);
	}
	return (i);
}

void	get_stat_rst(t_dirent_list *dirent_list)
{
	dirent_list->infos->mode = 0;
	dirent_list->infos->nlink = 0;
	dirent_list->infos->uid = 0;
	dirent_list->infos->gid = 0;
	dirent_list->infos->size = 0;
	dirent_list->infos->blocks = 0;
	dirent_list->infos->mtime = 0;
	dirent_list->infos->mtime_nsec = 0;
	dirent_list->infos->rdev = 0;
	dirent_list->infos->atime = 0;
}
