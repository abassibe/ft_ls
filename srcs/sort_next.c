/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 03:04:23 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/03 05:29:05 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_alpha_next(t_data *data, struct stat stat_tmp, t_dirent_list *tmp)
{
	data->file->stat = data->file->next->stat;
	data->file->next->stat = stat_tmp;
	tmp->child = data->file->child;
	data->file->child = data->file->next->child;
	data->file->next->child = tmp->child;
}

void	sort_alpha(t_data *data, int i, int c)
{
	t_dirent_list	*addr;
	t_dirent_list	*tmp;
	struct stat		stat_tmp;

	if (!(tmp = (t_dirent_list *)malloc(sizeof(t_dirent_list))))
		ft_error("MALLOC FAILED");
	addr = data->file;
	while (i < data->nb_file)
	{
		if (c == 0)
		{
			data->file = addr;
			i++;
			c = data->nb_file - i;
		}
		if (c > 1 && (ft_strcmp(NAME, NEXT_NAME) > 0))
		{
			stat_tmp = data->file->stat;
			sort_alpha_next(data, stat_tmp, tmp);
		}
		else if (c > 1)
			data->file = data->file->next;
		c--;
	}
	data->file = addr;
}

void	sort_time_next(t_data *data, t_dirent_list *tmp, int c, int i)
{
	struct dirent	*dirent_tmp;
	struct stat		stat_tmp;

	while (i < data->nb_file - 1)
	{
		if (c < 2)
		{
			data->file = data->file->next;
			tmp = data->file->next;
			i++;
			c = data->nb_file - i;
		}
		if (c > 1 && (data->file->stat.st_mtime < tmp->stat.st_mtime))
		{
			stat_tmp = data->file->stat;
			data->file->stat = tmp->stat;
			tmp->stat = stat_tmp;
			dirent_tmp = data->file->child;
			data->file->child = tmp->child;
			tmp->child = dirent_tmp;
		}
		c--;
		if (c > 1)
			tmp = tmp->next;
	}
}

void	sort_time(t_data *data, int i, int c)
{
	t_dirent_list	*addr;
	t_dirent_list	*tmp;

	if (!(tmp = (t_dirent_list *)malloc(sizeof(t_dirent_list))))
		ft_error("MALLOC FAILED");
	tmp = data->file->next;
	addr = data->file;
	sort_time_next(data, tmp, c, i);
	data->file = addr;
}
