/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 04:10:27 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/16 06:03:19 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_name_no_opt(t_data *data, t_dirent_list *file)
{
	if (S_ISDIR(file->infos->mode))
		ft_printf("{cyan}%-*s", data->len_max_name + 1, file->infos->name);
	else if (S_ISREG(file->infos->mode))
		ft_printf("%-*s", data->len_max_name + 1, file->infos->name);
	else if (file->infos->d_type == 10)
		ft_printf("{purple}%-*s", data->len_max_name + 1, file->infos->name);
	else if (S_ISCHR(file->infos->mode))
		ft_printf("{yellow}%-*s", data->len_max_name + 1, file->infos->name);
	else if (S_ISBLK(file->infos->mode))
		ft_printf("{green}%-*s", data->len_max_name + 1, file->infos->name);
	else if (S_ISFIFO(file->infos->mode))
		ft_printf("{red}%-*s", data->len_max_name + 1, file->infos->name);
	else if (S_ISSOCK(file->infos->mode))
		ft_printf("{blue}%-*s", data->len_max_name + 1, file->infos->name);
}

void	no_opt_print_next(t_data *data, int *len, int *i, int c)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	print_name_no_opt(data, data->file);
	(*len) += data->len_max_name + 1;
	data->file = data->file->next;
	(*i)++;
	if (*i < c - 1 && (*len + (data->len_max_name * 2) + 1 >= w.ws_col))
	{
		print_name_no_opt(data, data->file);
		ft_printf("\n");
		(*len) = 0;
		data->file = data->file->next;
		(*i)++;
	}
}

void	no_opt_print(t_data *data, int i, int c)
{
	int				len;

	len = 0;
	while (i < c)
	{
		if ((!ft_strchr(data->options_set, 'a')) &&
				data->file->infos->name[0] == '.')
		{
			data->file = data->file->next;
			i++;
		}
		else
			no_opt_print_next(data, &len, &i, c);
	}
	write(1, "\n", 1);
}

void	ft_print(t_data *data)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (ft_strchr(data->options_set, 'l'))
		l_print(data, i, k);
	else if (ft_strchr(data->options_set, '1'))
		one_print(data, i);
	else
	{
		k = data->nb_file;
		no_opt_print(data, i, k);
	}
	closedir(data->directory->rep);
}
