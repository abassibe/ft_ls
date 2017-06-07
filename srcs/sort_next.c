/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_next.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abassibe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/03 03:04:23 by abassibe          #+#    #+#             */
/*   Updated: 2017/06/07 02:53:40 by abassibe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	sort_swap(t_data *data, struct stat stat_tmp, t_dirent_list *tmp)
{
	stat_tmp = data->file->stat;
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

	stat_tmp = data->file->stat;
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
			sort_swap(data, stat_tmp, tmp);
		if (c > 1)
			data->file = data->file->next;
		c--;
	}
	data->file = addr;
}

void	sort_time(t_data *data, int i, int c)
{
	t_dirent_list	*addr;
	t_dirent_list	*tmp;
	struct stat		stat_tmp;

	stat_tmp = data->file->stat;
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
			sort_swap(data, stat_tmp, tmp);
		else if (c > 1 && (data->file->stat.st_mtimespec.tv_nsec < data->file->next->stat.st_mtimespec.tv_nsec))
			sort_swap(data, stat_tmp, tmp);
		if (c > 1)
			data->file = data->file->next;
		c--;
	}
	data->file = addr;
}
