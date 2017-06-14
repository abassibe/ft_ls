/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recurs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 02:48:45 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/14 06:09:11 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	search_directory(t_data *data, char **av, DIR *rep, int i)
{
	struct dirent	*dir;
	char			**str;

	str = malloc(sizeof(char **) * 1);
	if (av[i])
		str[0] = ft_strdup(av[i]);
	else
		str[0] = ft_strdup("./");
	while ((dir = readdir(rep)))
	{
		if (dir->d_type == 4 && !(ft_strequ(dir->d_name, ".")) && !(ft_strequ(dir->d_name, "..")))
		{
			str[0] = ft_strjoin(str[0], dir->d_name);
			ft_printf("\n%s:\n", str[0]);
			ft_init_data(str, data, 0);
			sort_lst(data);
			ft_print(data);
			str[0] = ft_strjoin(str[0], "/");
			if (!(rep = opendir(str[0])))
				ft_error("OPEN DIRECTORY FAILED");
			search_directory(data, str, rep, 0);
		}
	}
}

void	recurs(t_data *data, char **av, int i)
{
	struct stat		sb;
	DIR				*rep;

	if (av[i])
	{
		if (stat(av[i], &sb) == -1)
			ft_error("stat");
		if (!S_ISDIR(sb.st_mode))
		{
			ft_printf("%s\n", av[i]);
			exit (0);
		}
		if (!(rep = opendir(av[i])))
			ft_error("OPEN DIRECTORY FAILED");
		ft_init_data(av, data, i);
		sort_lst(data);
		ft_print(data);
		search_directory(data, av, rep, i);
	}
	else
	{
		if (stat("./", &sb) == -1)
			ft_error("stat");
		if (!S_ISDIR(sb.st_mode))
		{
			ft_init_data(av, data, i);
			exit (0);
		}
		if (!(rep = opendir("./")))
			ft_error("OPEN DIRECTORY FAILED");
		ft_init_data(av, data, i);
		sort_lst(data);
		ft_print(data);
		search_directory(data, av, rep, i);
	}
}
