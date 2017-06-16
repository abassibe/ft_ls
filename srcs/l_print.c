/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 03:06:27 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/16 06:12:11 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	mode_type_file(t_info *infos)
{
	if (infos->d_type == 10)
		write(1, "l", 1);
	else if (S_ISREG(infos->mode))
		write(1, "-", 1);
	else if (S_ISDIR(infos->mode))
		write(1, "d", 1);
	else if (S_ISCHR(infos->mode))
		write(1, "c", 1);
	else if (S_ISBLK(infos->mode))
		write(1, "b", 1);
	else if (S_ISFIFO(infos->mode))
		write(1, "p", 1);
	else if (S_ISSOCK(infos->mode))
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

void	mode_right(t_info *infos)
{
	char	*perm;
	int		i;
	int		j;

	j = 0;
	ft_sprintf(&perm, "%lo\n", (unsigned long)infos->mode);
	i = (int)ft_strlen(perm) - 4;
	while (j < 3)
	{
		mode_right_next(perm[i]);
		i++;
		j++;
	}
}

void	maj_min_bloc_print(t_data *data, t_dirent_list *file)
{
	if (data->chk == 1)
	{
		if (S_ISCHR(file->infos->mode) ||
				S_ISBLK(file->infos->mode))
		{
			ft_printf("%4d,", (MAJOR(file->infos->rdev) / 16));
			ft_printf("%4d ", MINOR(file->infos->rdev));
		}
		else
			write(1, "    ", 4);
	}
}

void	l_print(t_data *data, int i, int k)
{
	l_print_next(data, &k);
	while (i < data->nb_file)
	{
		if ((!ft_strchr(data->options_set, 'a')) &&
				data->file->infos->name[0] == '.')
		{
			data->file = data->file->next;
			i++;
		}
		else
		{
			mode_type_file(data->file->infos);
			mode_right(data->file->infos);
			ft_printf("%*u", k + 2, data->file->infos->nlink);
			ft_printf(" %-*s ", data->max_name, data->file->infos->pw_name);
			ft_printf(" %-*s ", data->max_grp, data->file->infos->gr_name);
			maj_min_bloc_print(data, data->file);
			display_size(data, data->file);
			print_date(data->file);
			print_name(data, data->file);
			data->file = data->file->next;
			i++;
		}
	}
}
