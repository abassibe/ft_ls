/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 03:06:27 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/08 04:58:51 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	mode_type_file(struct stat stat)
{
	if (S_ISLNK(stat.st_mode))
		write(1, "l", 1);
	else if (S_ISREG(stat.st_mode))
		write(1, "-", 1);
	else if (S_ISDIR(stat.st_mode))
		write(1, "d", 1);
	else if (S_ISCHR(stat.st_mode))
		write(1, "b", 1);
	else if (S_ISBLK(stat.st_mode))
		write(1, "c", 1);
	else if (S_ISFIFO(stat.st_mode))
		write(1, "p", 1);
	else if (S_ISSOCK(stat.st_mode))
		write(1, "s", 1);
}

void	mode_right_next(char c)
{
	if (c == '7')
		write(1, "rwx", 3);
	else if (c == '6')
		write(1, "rw-", 3);
	else if (c == '5')
		write(1, "r-x", 3);
	else if (c == '4')
		write(1, "r--", 3);
	else if (c == '3')
		write(1, "-wx", 3);
	else if (c == '2')
		write(1, "-w-", 3);
	else if (c == '1')
		write(1, "--x", 3);
	else
		write(1, "---", 3);
}

void	mode_right(struct stat stat)
{
	char	*perm;
	int		i;
	int		j;

	j = 0;
	ft_sprintf(&perm, "%lo\n", (unsigned long) stat.st_mode);
	i = (int)ft_strlen(perm) - 4;
	while (j < 3)
	{
		mode_right_next(perm[i]);
		i++;
		j++;
	}
}

void	display_size(t_data *data, t_dirent_list *file)
{
	int		i;
	int		j;

	i = 0;
	j = data->max_size;
	while (j > 0)
	{
		j /= 10;
		i++;
	}
	ft_printf("%*d ", i + 1, file->stat.st_size);
}

void	l_print(t_data *data)
{
	int		i;
	int		c;
	int		k;

	i = 0;
	k = 0;
	c = data->nb_file;
	l_print_next(data, &k);
	while (i < c)
	{
		while ((!ft_strchr(data->options_set, 'a')) && data->file->child->d_name[0] == '.')
		{
			data->file = data->file->next;
			i++;
		}
		mode_type_file(data->file->stat);
		mode_right(data->file->stat);
		ft_printf("%*u", k + 2, data->file->stat.st_nlink);
		ft_printf(" %-*s ", data->max_name, data->file->pwuid->pw_name);
		ft_printf(" %-*s ", data->max_grp, data->file->getgrp->gr_name);
		display_size(data, data->file);
		print_date(data->file);
		print_name(data->file);
		data->file = data->file->next;
		i++;
	}
}
