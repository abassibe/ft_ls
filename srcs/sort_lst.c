/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 02:50:12 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/03 05:26:50 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_rev(t_dirent_list *file, int i)
{
	t_dirent_list	*first;
	t_dirent_list	*rest;

	if (!file)
		return ;
	first = file;
	rest = first->next;
	if (!rest)
		return ;
	sort_rev(rest, i);
	i++;
	first->next->next = first;
	first->next = NULL;
}

t_dirent_list	*save_last_link(t_data *data, int i, int c)
{
	t_dirent_list	*addr;
	t_dirent_list	*addr2;

	addr = data->file;
	while (i < c - 1)
	{
		data->file = data->file->next;
		i++;
	}
	addr2 = data->file;
	data->file->next = NULL;
	data->file = addr;
	return (addr2);
}

void	sort_lst(t_data *data)
{
	int		i;
	int		c;
	t_dirent_list	*addr;

	i = 0;
	c = data->nb_file;
	sort_alpha(data, i, c);
	if (ft_strchr(data->options_set, 't'))
		sort_time(data, i, c);
	if (ft_strchr(data->options_set, 'r'))
	{
		addr = save_last_link(data, i, c);
		sort_rev(data->file, i);
		data->file = addr;
	}
}
