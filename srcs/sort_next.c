/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 03:04:23 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/10 01:16:13 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_swap(t_data *data, t_info *tmp)
{
	tmp = data->file->infos;
	data->file->infos = data->file->next->infos;
	data->file->next->infos = tmp;
}

void	sort_alpha(t_data *data, int i, int c)
{
	t_dirent_list	*addr;
	t_info			*tmp;

	if (!(tmp = (t_info *)malloc(sizeof(t_info))))
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
		if (c > 1 && (ft_strcmp(data->file->infos->name, data->file->next->infos->name) > 0))
			sort_swap(data, tmp);
		data->file = data->file->next;
		c--;
	}
	data->file = addr;
}

void	sort_time(t_data *data, int i, int c)
{
	t_dirent_list	*addr;
	t_info			*tmp;

	if (!(tmp = (t_info *)malloc(sizeof(t_info))))
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
		if (c > 1 && (data->file->infos->mtime < data->file->next->infos->mtime))
			sort_swap(data, tmp);
		else if (c > 1 && (data->file->infos->mtime_nsec < data->file->next->infos->mtime_nsec))
			sort_swap(data, tmp);
		data->file = data->file->next;
		c--;
	}
	data->file = addr;
}
