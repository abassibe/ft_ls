/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 04:10:27 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/07 03:07:32 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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
		ft_printf("%-*s", data->len_max_name + 1, data->file->child->d_name);
		len += data->len_max_name + 1;
		data->file = data->file->next;
		i++;
		if (i < c - 1 && (len + (data->len_max_name * 2) + 1 >= w.ws_col))
		{
			ft_printf("%-s", data->file->child->d_name);
			ft_printf("\n");
			len = 0;
			data->file = data->file->next;
			i++;
		}
	}
}

void	ft_print(t_data *data)
{
	if (ft_strchr(data->options_set, 'l'))
		l_print(data);
	else
		no_opt_print(data);
}
