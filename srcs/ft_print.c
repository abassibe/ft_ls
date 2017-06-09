/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 04:10:27 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/09 05:26:01 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_name_no_opt(t_data *data, t_dirent_list *file)
{
	if (S_ISDIR(file->infos->mode))
		ft_printf(" {cyan}%-*s", data->len_max_name, file->infos->name);
	else if (S_ISREG(file->infos->mode))
		ft_printf(" %-*s", data->len_max_name, file->infos->name);
	else if (file->infos->d_type == 10)
		ft_printf(" {purple}%-*s", data->len_max_name, file->infos->name);
	else if (S_ISCHR(file->infos->mode))
		ft_printf(" {yellow}%-*s", data->len_max_name, file->infos->name);
	else if (S_ISBLK(file->infos->mode))
		ft_printf(" {green}%-*s", data->len_max_name, file->infos->name);
	else if (S_ISFIFO(file->infos->mode))
		ft_printf(" {red}%-*s", data->len_max_name, file->infos->name);
	else if (S_ISSOCK(file->infos->mode))
		ft_printf(" {blue}%-*s", data->len_max_name, file->infos->name);
}

void	no_opt_print(t_data *data)
{
	int				i;
	int				c;
	int				len;
	struct winsize	w;

	i = 0;
	len = 0;
	c = data->nb_file;
	ioctl(0, TIOCGWINSZ, &w);
	while (i < c)
	{
		while ((!ft_strchr(data->options_set, 'a')) && data->file->infos->name[0] == '.')
		{
			data->file = data->file->next;
			i++;
		}
		print_name_no_opt(data, data->file);
		len += data->len_max_name + 1;
		data->file = data->file->next;
		i++;
		if (i < c - 1 && (len + (data->len_max_name * 2) + 1 >= w.ws_col))
		{
		print_name_no_opt(data, data->file);
			ft_printf("\n");
			len = 0;
			data->file = data->file->next;
			i++;
		}
	}
	write(1, "\n", 1);
}

void	ft_print(t_data *data)
{
	if (ft_strchr(data->options_set, 'l'))
		l_print(data);
	else
		no_opt_print(data);
}
