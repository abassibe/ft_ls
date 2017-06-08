/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 03:04:23 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/08 05:57:41 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_swap(t_data *data, t_dirent_list *tmp)
{
	tmp->stat = data->file->stat;
	data->file->stat = data->file->next->stat;
	data->file->next->stat = tmp->stat;
	tmp->pwuid = data->file->pwuid;
	data->file->pwuid = data->file->next->pwuid;
	data->file->next->pwuid = tmp->pwuid;
	tmp->getgrp = data->file->getgrp;
	data->file->getgrp = data->file->next->getgrp;
	data->file->next->getgrp = tmp->getgrp;
	tmp->child = data->file->child;
	data->file->child = data->file->next->child;
	data->file->next->child = tmp->child;
}

void	sort_alpha(t_data *data, int i, int c)
{
	t_dirent_list	*addr;
	t_dirent_list	*tmp;

	if (!(tmp = (t_dirent_list *)malloc(sizeof(t_dirent_list))))
		ft_error("MALLOC FAILED");
	addr = data->file;
	while (i < data->nb_file)
	{
		if (c == 0)
		{
			data->file = addr;
			i++;
			c = data->nb_file;
		}
		if (c > 1 && (ft_strcmp(NAME, NEXT_NAME) > 0))
			sort_swap(data, tmp);
		data->file = data->file->next;
		c--;
	}
	data->file = addr;
}

void	sort_time(t_data *data, int i, int c)
{
	t_dirent_list	*addr;
	t_dirent_list	*tmp;

	if (!(tmp = (t_dirent_list *)malloc(sizeof(t_dirent_list))))
		ft_error("MALLOC FAILED");
	addr = data->file;
	while (i < data->nb_file)
	{
		if (c == 0)
		{
			data->file = addr;
			i++;
			c = data->nb_file;
		}
		if (c > 1 && (data->file->stat.st_mtime < data->file->next->stat.st_mtime))
			sort_swap(data, tmp);
		else if (c > 1 && (data->file->stat.st_mtimespec.tv_nsec < data->file->next->stat.st_mtimespec.tv_nsec))
			sort_swap(data, tmp);
		data->file = data->file->next;
		c--;
	}
	data->file = addr;
}
